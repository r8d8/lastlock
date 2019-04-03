/*
 * Amazon FreeRTOS
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

/* Standard includes. */
#include <stdlib.h>
#include <string.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "FreeRTOSIPConfig.h"
#include "task.h"
#include "event_groups.h"

/* Crypto includes. */
#include "aws_crypto.h"
#include "aws_clientcredential.h"
#include "aws_pkcs11.h"
#include "aws_dev_mode_key_provisioning.h"
#include "aws_test_pkcs11_config.h"

/* Test includes. */
#include "unity_fixture.h"
#include "unity.h"

/* mbedTLS includes. */
//#include "mbedtls/sha256.h"
//#include "mbedtls/x509_crt.h"
#include "qapi_crypto.h"

/*-----------------------------------------------------------*/
/*         Multitask sign-verify loop configuration.         */
/*-----------------------------------------------------------*/
/* Stack size of each task. */
#define pkcs11testSIGN_VERIFY_TASK_STACK_SIZE    ( configMINIMAL_STACK_SIZE * 4 )
/* Priority of each task. */
#define pkcs11testSIGN_VERIFY_TASK_PRIORITY      ( tskIDLE_PRIORITY )
/* Specifies bits for all tasks to the event group. */
#define pkcs11testALL_BITS                       ( ( 1 << pkcs11testSIGN_VERIFY_TASK_COUNT ) - 1 )

/* Parameters to each task. */
typedef struct SignVerifyTaskParams
{
    BaseType_t xTaskNumber;
    CK_RV xTestResult;
} SignVerifyTaskParams_t;

/* Event group used to synchronize tasks. */
static EventGroupHandle_t xSyncEventGroup;

/*-----------------------------------------------------------*/
/*                Certificates used in tests.                */
/*-----------------------------------------------------------*/

/* Valid ECDSA certificate. */
static const char pcValidECDSACertificate[] =
    "-----BEGIN CERTIFICATE-----\n"
    "MIIBVDCB+6ADAgECAgkAoJ9fIf9ayYswCgYIKoZIzj0EAwIwHTEbMBkGA1UEAwwS\n"
    "bm9ib2R5QG5vd2hlcmUuY29tMB4XDTE4MDMwODIyNDIzNFoXDTE5MDMwODIyNDIz\n"
    "NFowHTEbMBkGA1UEAwwSbm9ib2R5QG5vd2hlcmUuY29tMFkwEwYHKoZIzj0CAQYI\n"
    "KoZIzj0DAQcDQgAExYJLN8zYGzFieyF4ONxk2BCY8I4fQTpfOJyWSYCqat83xtNE\n"
    "KoOxB33FP22MJXn7rj24YILu1uRLrFkH2pcRkKMkMCIwCwYDVR0PBAQDAgeAMBMG\n"
    "A1UdJQQMMAoGCCsGAQUFBwMDMAoGCCqGSM49BAMCA0gAMEUCIQDhXUT02TsIlzBe\n"
    "Aw9pLCowZ+6dPY1igspplUqZcuDAKQIgN6j5s7x5AudklULRuFyBQBlkVR35IdWs\n"
    "zu/xp2COg9g=\n"
    "-----END CERTIFICATE-----";

/* This ECDSA certificate is malformed. The first 'M' has been replaced with a 'Z'. */
static const char pcInvalidECDSACertificate[] =
    "-----BEGIN CERTIFICATE-----\n"
    "ZIIBVDCB+6ADAgECAgkAoJ9fIf9ayYswCgYIKoZIzj0EAwIwHTEbMBkGA1UEAwwS\n"
    "bm9ib2R5QG5vd2hlcmUuY29tMB4XDTE4MDMwODIyNDIzNFoXDTE5MDMwODIyNDIz\n"
    "NFowHTEbMBkGA1UEAwwSbm9ib2R5QG5vd2hlcmUuY29tMFkwEwYHKoZIzj0CAQYI\n"
    "KoZIzj0DAQcDQgAExYJLN8zYGzFieyF4ONxk2BCY8I4fQTpfOJyWSYCqat83xtNE\n"
    "KoOxB33FP22MJXn7rj24YILu1uRLrFkH2pcRkKMkMCIwCwYDVR0PBAQDAgeAMBMG\n"
    "A1UdJQQMMAoGCCsGAQUFBwMDMAoGCCqGSM49BAMCA0gAMEUCIQDhXUT02TsIlzBe\n"
    "Aw9pLCowZ+6dPY1igspplUqZcuDAKQIgN6j5s7x5AudklULRuFyBQBlkVR35IdWs\n"
    "zu/xp2COg9g=\n"
    "-----END CERTIFICATE-----";

/* Valid ECDSA private key. */
static const char pcValidECDSAPrivateKey[] =
    "-----BEGIN PRIVATE KEY-----\n"
    "MIGHAgEAMBMGByqGSM49AgEGCCqGSM49AwEHBG0wawIBAQQg8gHhd5ELAooWRQls\n"
    "PfpcQREiLrvEb3oLioicMYdUmrmhRANCAATFgks3zNgbMWJ7IXg43GTYEJjwjh9B\n"
    "Ol84nJZJgKpq3zfG00Qqg7EHfcU/bYwlefuuPbhggu7W5EusWQfalxGQ\n"
    "-----END PRIVATE KEY-----";

/* This ECDSA private key is malformed. The first 'M' has been replaced with a 'Z'. */
static const char pcInvalidECDSAPrivateKey[] =
    "-----BEGIN PRIVATE KEY-----\n"
    "ZIGHAgEAMBMGByqGSM49AgEGCCqGSM49AwEHBG0wawIBAQQg8gHhd5ELAooWRQls\n"
    "PfpcQREiLrvEb3oLioicMYdUmrmhRANCAATFgks3zNgbMWJ7IXg43GTYEJjwjh9B\n"
    "Ol84nJZJgKpq3zfG00Qqg7EHfcU/bYwlefuuPbhggu7W5EusWQfalxGQ\n"
    "-----END PRIVATE KEY-----";

/* This is the public key that pairs with pcValidECDSAPrivateKey. */
static const char pcValidECDSAPublicKey[] =
    "-----BEGIN PUBLIC KEY-----\n"
    "MFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAExYJLN8zYGzFieyF4ONxk2BCY8I4f\n"
    "QTpfOJyWSYCqat83xtNEKoOxB33FP22MJXn7rj24YILu1uRLrFkH2pcRkA==\n"
    "-----END PUBLIC KEY-----";

/* This ECDSA public key malformed. The first 'M' has been replaced with a 'Z'. */
static const char pcInvalidECDSAPublicKey[] =
    "-----BEGIN PUBLIC KEY-----\n"
    "ZFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAExYJLN8zYGzFieyF4ONxk2BCY8I4f\n"
    "QTpfOJyWSYCqat83xtNEKoOxB33FP22MJXn7rj24YILu1uRLrFkH2pcRkA==\n"
    "-----END PUBLIC KEY-----";

/* This is a valid public key, but isn't paired with pcValidECDSAPrivateKey. */
static const char pcWrongECDSAPublicKey[] =
    "-----BEGIN PUBLIC KEY-----\n"
    "MFYwEAYHKoZIzj0CAQYFK4EEAAoDQgAEWp505KT6CprrMbGH/j3POjmbuPPIG6W7\n"
    "Dz/Yy4EF6EkfJ+cdPurX7BkKr9ZZ12u1nbNp/BQNQULv8pcdx+jd7Q==\n"
    "-----END PUBLIC KEY-----";

/* Valid RSA certificate. */
static const char pcValidRSACertificate[] =
    "-----BEGIN CERTIFICATE-----\n"
    "MIIEFTCCAv2gAwIBAgIJAOHcumPypB/gMA0GCSqGSIb3DQEBCwUAMIGgMQswCQYD\n"
    "VQQGEwJVUzELMAkGA1UECAwCV0ExEDAOBgNVBAcMB1NlYXR0bGUxGTAXBgNVBAoM\n"
    "EFRlc3QgY2VydGlmaWNhdGUxGTAXBgNVBAsMEFRlc3QgY2VydGlmaWNhdGUxGTAX\n"
    "BgNVBAMMEFRlc3QgY2VydGlmaWNhdGUxITAfBgkqhkiG9w0BCQEWEm5vYm9keUBu\n"
    "b3doZXJlLmNvbTAeFw0xODAzMDkyMjI2MDFaFw0xOTAzMDkyMjI2MDFaMIGgMQsw\n"
    "CQYDVQQGEwJVUzELMAkGA1UECAwCV0ExEDAOBgNVBAcMB1NlYXR0bGUxGTAXBgNV\n"
    "BAoMEFRlc3QgY2VydGlmaWNhdGUxGTAXBgNVBAsMEFRlc3QgY2VydGlmaWNhdGUx\n"
    "GTAXBgNVBAMMEFRlc3QgY2VydGlmaWNhdGUxITAfBgkqhkiG9w0BCQEWEm5vYm9k\n"
    "eUBub3doZXJlLmNvbTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKi1\n"
    "yl21b11RVCat+ttuA3CLjfA7A0MocHlnjPvp71u+RY5SWRTSlObg+wMbJqXSLZoR\n"
    "oN1ZF/+EZw6mDAIDbnfNi7wLt5Ztkdggfm9M128ShsIkzMC/oE4ySoKANNveyiqN\n"
    "0wVCqepeIwBE6e74qOCO7Jen1MAySicIPAGRQVmBlA2AjxNlEhCMyJosal0YqQHM\n"
    "VVTa7d1+IQZhAniFZGD1KfSEemTAEzrBN0dcPuFqYqnFZW6tZa7FSbt5YcIHEZSF\n"
    "CLSEnoXiNRB1uamztaegCpw3L1NDV0Uq7UBIXWyi4r3pXjXdmj7rEuAYR47DVkCV\n"
    "ZrEhI8QJDsptElibq8MCAwEAAaNQME4wHQYDVR0OBBYEFFEmc65Gwo+92RNFYWBz\n"
    "fJRTkQByMB8GA1UdIwQYMBaAFFEmc65Gwo+92RNFYWBzfJRTkQByMAwGA1UdEwQF\n"
    "MAMBAf8wDQYJKoZIhvcNAQELBQADggEBAJdQn2Y2dWzXwn0NJbznyLe6g9w0NVk4\n"
    "FR/sH+awqt5RVWYCXbKK8eNl4tKnDM7rXfKVEnCvNbNpJhGKpK9r9ubTe/iK2Hi4\n"
    "vXSicIvwOOp6hm6jLSjwqymfPbZ+1yP0RWN8tFhU51pZq/u7yoJsWQm9VeAyZ2kg\n"
    "Ktfp0D5VlQCrZn3cxs8GP41EbyBAZHyCEVGH8l4Abx4FfBqz+9ASk6CJxYyYEkGj\n"
    "A5QUzMXRWLw2b9L5MSHRnisRr2fAQ6GQHeQuFIPmTVW9wrg5vYKQD9qZC85vB0tN\n"
    "mbs0MzsUwVc8U2A1wbEzVurvXPwtBeBGC1Kq/2mMxdpPHxas6w5eBVo=\n"
    "-----END CERTIFICATE-----";

/* This RSA certificate is malformed. The first 'M' has been replaced with a 'Z'. */
static const char pcInvalidRSACertificate[] =
    "-----BEGIN CERTIFICATE-----\n"
    "ZIIEFTCCAv2gAwIBAgIJAOHcumPypB/gMA0GCSqGSIb3DQEBCwUAMIGgMQswCQYD\n"
    "VQQGEwJVUzELMAkGA1UECAwCV0ExEDAOBgNVBAcMB1NlYXR0bGUxGTAXBgNVBAoM\n"
    "EFRlc3QgY2VydGlmaWNhdGUxGTAXBgNVBAsMEFRlc3QgY2VydGlmaWNhdGUxGTAX\n"
    "BgNVBAMMEFRlc3QgY2VydGlmaWNhdGUxITAfBgkqhkiG9w0BCQEWEm5vYm9keUBu\n"
    "b3doZXJlLmNvbTAeFw0xODAzMDkyMjI2MDFaFw0xOTAzMDkyMjI2MDFaMIGgMQsw\n"
    "CQYDVQQGEwJVUzELMAkGA1UECAwCV0ExEDAOBgNVBAcMB1NlYXR0bGUxGTAXBgNV\n"
    "BAoMEFRlc3QgY2VydGlmaWNhdGUxGTAXBgNVBAsMEFRlc3QgY2VydGlmaWNhdGUx\n"
    "GTAXBgNVBAMMEFRlc3QgY2VydGlmaWNhdGUxITAfBgkqhkiG9w0BCQEWEm5vYm9k\n"
    "eUBub3doZXJlLmNvbTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKi1\n"
    "yl21b11RVCat+ttuA3CLjfA7A0MocHlnjPvp71u+RY5SWRTSlObg+wMbJqXSLZoR\n"
    "oN1ZF/+EZw6mDAIDbnfNi7wLt5Ztkdggfm9M128ShsIkzMC/oE4ySoKANNveyiqN\n"
    "0wVCqepeIwBE6e74qOCO7Jen1MAySicIPAGRQVmBlA2AjxNlEhCMyJosal0YqQHM\n"
    "VVTa7d1+IQZhAniFZGD1KfSEemTAEzrBN0dcPuFqYqnFZW6tZa7FSbt5YcIHEZSF\n"
    "CLSEnoXiNRB1uamztaegCpw3L1NDV0Uq7UBIXWyi4r3pXjXdmj7rEuAYR47DVkCV\n"
    "ZrEhI8QJDsptElibq8MCAwEAAaNQME4wHQYDVR0OBBYEFFEmc65Gwo+92RNFYWBz\n"
    "fJRTkQByMB8GA1UdIwQYMBaAFFEmc65Gwo+92RNFYWBzfJRTkQByMAwGA1UdEwQF\n"
    "MAMBAf8wDQYJKoZIhvcNAQELBQADggEBAJdQn2Y2dWzXwn0NJbznyLe6g9w0NVk4\n"
    "FR/sH+awqt5RVWYCXbKK8eNl4tKnDM7rXfKVEnCvNbNpJhGKpK9r9ubTe/iK2Hi4\n"
    "vXSicIvwOOp6hm6jLSjwqymfPbZ+1yP0RWN8tFhU51pZq/u7yoJsWQm9VeAyZ2kg\n"
    "Ktfp0D5VlQCrZn3cxs8GP41EbyBAZHyCEVGH8l4Abx4FfBqz+9ASk6CJxYyYEkGj\n"
    "A5QUzMXRWLw2b9L5MSHRnisRr2fAQ6GQHeQuFIPmTVW9wrg5vYKQD9qZC85vB0tN\n"
    "mbs0MzsUwVc8U2A1wbEzVurvXPwtBeBGC1Kq/2mMxdpPHxas6w5eBVo=\n"
    "-----END CERTIFICATE-----";

/* Valid RSA private key. */
static const char pcValidRSAPrivateKey[] =
    "-----BEGIN PRIVATE KEY-----\n"
    "MIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQCotcpdtW9dUVQm\n"
    "rfrbbgNwi43wOwNDKHB5Z4z76e9bvkWOUlkU0pTm4PsDGyal0i2aEaDdWRf/hGcO\n"
    "pgwCA253zYu8C7eWbZHYIH5vTNdvEobCJMzAv6BOMkqCgDTb3soqjdMFQqnqXiMA\n"
    "ROnu+KjgjuyXp9TAMkonCDwBkUFZgZQNgI8TZRIQjMiaLGpdGKkBzFVU2u3dfiEG\n"
    "YQJ4hWRg9Sn0hHpkwBM6wTdHXD7hamKpxWVurWWuxUm7eWHCBxGUhQi0hJ6F4jUQ\n"
    "dbmps7WnoAqcNy9TQ1dFKu1ASF1souK96V413Zo+6xLgGEeOw1ZAlWaxISPECQ7K\n"
    "bRJYm6vDAgMBAAECggEAOAN7d9dobSQ2e00iT75b9/7tlkgRkjeX+EbwISePZ/dp\n"
    "YpJmryonc+xYirR2BXId39xge308IYLVMKDitbxr7ezZqwp83r3sQUSwlcV+dYtC\n"
    "IK1VKd21nKDH6kIkyqdSmgRSfpmejojIuCspPEVk1IG/fa6kTVelFQZ/3clbWBrK\n"
    "iMFTKHAe4vm+tQiEviDysMGTpWjyX7uf7Q814Nm0u6sJ2x4CGCQ3AgnxrU3k+PMl\n"
    "UYTfN7PCqRBg6eFn6ZsLBEbFTtKSZ+8Vc633zjOq92W6tA5eTKUxhXdEdH+y+M9a\n"
    "P8d6HDN+MB9M4oBkz2YIsqWMfxl3qLrYYPWWumJvwQKBgQDSsNXhIgxAw+5LbhEl\n"
    "sxwf307DF7bf3/qxUD3yrjl2ApAOUQb29u2Z/A/V9Gal8KwYMkPgFKW2vbFPjaFK\n"
    "WsCCyHNMZ1oAkMcDU8NqNCKuQI5lP5N8wdcSFUlefadnCZ+/D5O3kVilmK0eesKh\n"
    "TqmlIR8OFK+vKT/4R4p/e1XpYwKBgQDM/cseBXNSI64s/qebUbcofJjutr1MreXk\n"
    "WBV/QOInmi1GlHe474HAIKUfxuYug4lzM7lfpinGWEhGJ+8nW2GoWPXqZwckYZZ6\n"
    "TtPk+1TxG1DrEs/KHDMx8W8DHAr2N0/0N+urwKeci0IwqOYrh5B1/plbmoafvtcN\n"
    "UCpbbUPyIQKBgQCb74eMxf9dm+Xta/xC88p4CHWpzQ5rqcFIpMQErlAW+JSYE/5c\n"
    "oKuAUV+DEg06+eLVUbaMzZtMoh7uazuZ5YsgAK3dOY0SaBTzcHZsT0PvxhXd9+z3\n"
    "5BuC5cBUsBlLGINkDGpe7bM3dMWEjoUokCjc76Olb0gMEzKmVoS6D5WpUwKBgAwN\n"
    "O7zXGzGQEXRpwFbcVgVWVfNq4PQ6IRLsrs7ddK5ZXSISJnvD8P/nq22T1wKTDyir\n"
    "uNFLxpb3p8AgJupMcBBisoqGZiAYcK1eJw0GTbcjIP3BDGBYihX8mMc5Bdf15oh4\n"
    "JS3i1LfaZBjSRT336WFWh5OgIRwRLzmEJglcAiuhAoGAX6c1CeSqqzru4J6FB/Le\n"
    "l1OeRDB5femizPbheBNYrnS/FV5RLUW3pcnqox8/D9gDOxcj14iJJgXOsmFUTlA4\n"
    "nC5lL1SFTo57vur+IaGdhd18Am3Ui2+Uv+W9j6Kiz+xMvW01u7zW3cSffsd+44IN\n"
    "wXfRtw5Zqux2XFy/iXhyB50=\n"
    "-----END PRIVATE KEY-----";

/* This RSA private key is malformed. The first 'M' has been replaced with a 'Z'. */
static const char pcInvalidRSAPrivateKey[] =
    "-----BEGIN PRIVATE KEY-----\n"
    "ZIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQCotcpdtW9dUVQm\n"
    "rfrbbgNwi43wOwNDKHB5Z4z76e9bvkWOUlkU0pTm4PsDGyal0i2aEaDdWRf/hGcO\n"
    "pgwCA253zYu8C7eWbZHYIH5vTNdvEobCJMzAv6BOMkqCgDTb3soqjdMFQqnqXiMA\n"
    "ROnu+KjgjuyXp9TAMkonCDwBkUFZgZQNgI8TZRIQjMiaLGpdGKkBzFVU2u3dfiEG\n"
    "YQJ4hWRg9Sn0hHpkwBM6wTdHXD7hamKpxWVurWWuxUm7eWHCBxGUhQi0hJ6F4jUQ\n"
    "dbmps7WnoAqcNy9TQ1dFKu1ASF1souK96V413Zo+6xLgGEeOw1ZAlWaxISPECQ7K\n"
    "bRJYm6vDAgMBAAECggEAOAN7d9dobSQ2e00iT75b9/7tlkgRkjeX+EbwISePZ/dp\n"
    "YpJmryonc+xYirR2BXId39xge308IYLVMKDitbxr7ezZqwp83r3sQUSwlcV+dYtC\n"
    "IK1VKd21nKDH6kIkyqdSmgRSfpmejojIuCspPEVk1IG/fa6kTVelFQZ/3clbWBrK\n"
    "iMFTKHAe4vm+tQiEviDysMGTpWjyX7uf7Q814Nm0u6sJ2x4CGCQ3AgnxrU3k+PMl\n"
    "UYTfN7PCqRBg6eFn6ZsLBEbFTtKSZ+8Vc633zjOq92W6tA5eTKUxhXdEdH+y+M9a\n"
    "P8d6HDN+MB9M4oBkz2YIsqWMfxl3qLrYYPWWumJvwQKBgQDSsNXhIgxAw+5LbhEl\n"
    "sxwf307DF7bf3/qxUD3yrjl2ApAOUQb29u2Z/A/V9Gal8KwYMkPgFKW2vbFPjaFK\n"
    "WsCCyHNMZ1oAkMcDU8NqNCKuQI5lP5N8wdcSFUlefadnCZ+/D5O3kVilmK0eesKh\n"
    "TqmlIR8OFK+vKT/4R4p/e1XpYwKBgQDM/cseBXNSI64s/qebUbcofJjutr1MreXk\n"
    "WBV/QOInmi1GlHe474HAIKUfxuYug4lzM7lfpinGWEhGJ+8nW2GoWPXqZwckYZZ6\n"
    "TtPk+1TxG1DrEs/KHDMx8W8DHAr2N0/0N+urwKeci0IwqOYrh5B1/plbmoafvtcN\n"
    "UCpbbUPyIQKBgQCb74eMxf9dm+Xta/xC88p4CHWpzQ5rqcFIpMQErlAW+JSYE/5c\n"
    "oKuAUV+DEg06+eLVUbaMzZtMoh7uazuZ5YsgAK3dOY0SaBTzcHZsT0PvxhXd9+z3\n"
    "5BuC5cBUsBlLGINkDGpe7bM3dMWEjoUokCjc76Olb0gMEzKmVoS6D5WpUwKBgAwN\n"
    "O7zXGzGQEXRpwFbcVgVWVfNq4PQ6IRLsrs7ddK5ZXSISJnvD8P/nq22T1wKTDyir\n"
    "uNFLxpb3p8AgJupMcBBisoqGZiAYcK1eJw0GTbcjIP3BDGBYihX8mMc5Bdf15oh4\n"
    "JS3i1LfaZBjSRT336WFWh5OgIRwRLzmEJglcAiuhAoGAX6c1CeSqqzru4J6FB/Le\n"
    "l1OeRDB5femizPbheBNYrnS/FV5RLUW3pcnqox8/D9gDOxcj14iJJgXOsmFUTlA4\n"
    "nC5lL1SFTo57vur+IaGdhd18Am3Ui2+Uv+W9j6Kiz+xMvW01u7zW3cSffsd+44IN\n"
    "wXfRtw5Zqux2XFy/iXhyB50=\n"
    "-----END PRIVATE KEY-----";

/* This is the public key that pairs with pcValidRSAPrivateKey. */
static const char pcValidRSAPublicKey[] =
    "-----BEGIN PUBLIC KEY-----\n"
    "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAqLXKXbVvXVFUJq36224D\n"
    "cIuN8DsDQyhweWeM++nvW75FjlJZFNKU5uD7AxsmpdItmhGg3VkX/4RnDqYMAgNu\n"
    "d82LvAu3lm2R2CB+b0zXbxKGwiTMwL+gTjJKgoA0297KKo3TBUKp6l4jAETp7vio\n"
    "4I7sl6fUwDJKJwg8AZFBWYGUDYCPE2USEIzImixqXRipAcxVVNrt3X4hBmECeIVk\n"
    "YPUp9IR6ZMATOsE3R1w+4WpiqcVlbq1lrsVJu3lhwgcRlIUItISeheI1EHW5qbO1\n"
    "p6AKnDcvU0NXRSrtQEhdbKLiveleNd2aPusS4BhHjsNWQJVmsSEjxAkOym0SWJur\n"
    "wwIDAQAB\n"
    "-----END PUBLIC KEY-----";

/* This RSA public key malformed. The first 'M' has been replaced with a 'Z'. */
static const char pcInvalidRSAPublicKey[] =
    "-----BEGIN PUBLIC KEY-----\n"
    "ZIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAqLXKXbVvXVFUJq36224D\n"
    "cIuN8DsDQyhweWeM++nvW75FjlJZFNKU5uD7AxsmpdItmhGg3VkX/4RnDqYMAgNu\n"
    "d82LvAu3lm2R2CB+b0zXbxKGwiTMwL+gTjJKgoA0297KKo3TBUKp6l4jAETp7vio\n"
    "4I7sl6fUwDJKJwg8AZFBWYGUDYCPE2USEIzImixqXRipAcxVVNrt3X4hBmECeIVk\n"
    "YPUp9IR6ZMATOsE3R1w+4WpiqcVlbq1lrsVJu3lhwgcRlIUItISeheI1EHW5qbO1\n"
    "p6AKnDcvU0NXRSrtQEhdbKLiveleNd2aPusS4BhHjsNWQJVmsSEjxAkOym0SWJur\n"
    "wwIDAQAB\n"
    "-----END PUBLIC KEY-----";

/* This is a valid public key, but isn't paired with pcValidRSAPrivateKey. */
static const char pcWrongRSAPublicKey[] =
    "-----BEGIN PUBLIC KEY-----\n"
    "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAmpfMnNQkv0yEQM3LPAy5\n"
    "LQwT0OL6hYkxIW05POB5hYifE/RIjeu+e25xFbEpXC7p9rFNrkn2C3gQE2X3Qjqy\n"
    "e8eQFpvO7Y+g64kn3DiHsTwuKf57Cyid/dAAFnHMixXTAArH7OwVnSj3oz18GM9x\n"
    "3Zx8nLA92yuclr0Z1LTZwiUBD7loTsA6X+e+RsYhQBMDMSfxflGGqOLmX4tPnE8+\n"
    "PsU0w9GeuHalW4CsVFQ2Sm7jL2gtrEQpGDSwzDmdqrSgY92NNrbjwFMd1lLSwQwP\n"
    "tlznpxGyGPkuetZWkVbaJ3wbUwxf1y+PXjYx1uwULrVeZR+JSrWeiez3DVHy2lRh\n"
    "WQIDAQAB\n"
    "-----END PUBLIC KEY-----";

/*-----------------------------------------------------------*/

/* The hash of the empty string "\0" (data). Calculated with OpenSSL 1.0.2g. */
static const char pcEmptyStringHash[] =
{
    0x6e, 0x34, 0x0b, 0x9c, 0xff, 0xb3, 0x7a, 0x98, 0x9c, 0xa5, 0x44, 0xe6,
    0xbb, 0x78, 0x0a, 0x2c, 0x78, 0x90, 0x1d, 0x3f, 0xb3, 0x37, 0x38, 0x76,
    0x85, 0x11, 0xa3, 0x06, 0x17, 0xaf, 0xa0, 0x1d
};
/* Data signed with pcValidPrivateKey using OpenSSL 1.0.2g. */
static const char pcSignedData[] =
{
    0x99, 0x6c, 0x6c, 0xeb, 0x49, 0x15, 0x0b, 0xef, 0xb6, 0xab, 0xed, 0xd2,
    0x61, 0x13, 0x39, 0x17, 0x91, 0xf2, 0x08, 0x9b, 0x96, 0x75, 0x99, 0x58,
    0x0d, 0xe6, 0x1d, 0xe6, 0x78, 0x1b, 0xfa, 0x90, 0xeb, 0xc1, 0x43, 0x6f,
    0xe5, 0x16, 0x29, 0x8b, 0x03, 0xac, 0x57, 0xef, 0xb8, 0x02, 0x0e, 0xb7,
    0x6e, 0x01, 0x2a, 0xfc, 0xd9, 0xc0, 0x96, 0x09, 0x1f, 0x73, 0x56, 0xb0,
    0xf0, 0xe6, 0x88, 0x05, 0xeb, 0x39, 0x7a, 0x88, 0x61, 0x99, 0x3f, 0x59,
    0xac, 0x7a, 0x3c, 0xdd, 0x3c, 0x9a, 0xb4, 0x78, 0x78, 0x2b, 0x76, 0xfb,
    0xb5, 0x22, 0x0c, 0x2b, 0x34, 0x99, 0x4a, 0x3a, 0x31, 0x5f, 0xb8, 0x7c,
    0x29, 0xda, 0x60, 0x66, 0x45, 0x63, 0x44, 0x50, 0x1f, 0xcd, 0x8d, 0xeb,
    0x66, 0x4c, 0x54, 0x93, 0x71, 0xab, 0xc5, 0x2a, 0x6c, 0x43, 0x1e, 0x5d,
    0xb5, 0xdc, 0x28, 0xdc, 0x9b, 0x1d, 0xed, 0x34, 0xa3, 0xe3, 0x1e, 0x37,
    0x22, 0x37, 0xda, 0xfd, 0x07, 0xdc, 0x41, 0x93, 0xe2, 0xfa, 0x98, 0x20,
    0x87, 0x88, 0xa3, 0x8f, 0x0c, 0x21, 0x88, 0x21, 0x20, 0x1b, 0x26, 0xd2,
    0xd4, 0xb9, 0x1b, 0x53, 0x7f, 0xc3, 0x82, 0x23, 0x02, 0x21, 0xb2, 0x8f,
    0xcb, 0x42, 0x03, 0x3d, 0xaf, 0x42, 0x66, 0xf1, 0xa7, 0xad, 0xa8, 0xf1,
    0xe2, 0xeb, 0x15, 0xd4, 0xd5, 0x19, 0x92, 0x51, 0x23, 0xa5, 0x21, 0xe0,
    0xbe, 0xd0, 0xfc, 0xf1, 0xf6, 0xd3, 0x3d, 0xc9, 0xd6, 0x1e, 0x4b, 0xf0,
    0x44, 0xd6, 0x4f, 0x92, 0xf2, 0x59, 0x48, 0x07, 0x6f, 0xb1, 0x8f, 0x09,
    0x60, 0x54, 0x29, 0x0e, 0xe5, 0x13, 0x06, 0x75, 0xdb, 0x36, 0x7c, 0xe9,
    0x0f, 0x81, 0xb4, 0xd6, 0x08, 0x9b, 0x3b, 0x5c, 0x1c, 0xdf, 0x0c, 0x2e,
    0x41, 0x88, 0x4a, 0x81, 0xd2, 0x75, 0x16, 0x99, 0xb1, 0x82, 0x2e, 0x16,
    0x6a, 0xb1, 0x31, 0xdc
};


/*-----------------------------------------------------------*/

static void prvReprovision( const char * const pcClientCertificate,
                            const char * const pcClientPrivateKey,
                            uint32_t ulClientPrivateKeyType )
{
    ProvisioningParams_t xParams;

    xParams.pcClientCertificate = ( uint8_t * ) pcClientCertificate;
    xParams.pcClientPrivateKey = ( uint8_t * ) pcClientPrivateKey;

    /* Include the null-terminator in cert and key length. */
    xParams.ulClientCertificateLength = strlen( pcClientCertificate ) + 1;
    xParams.ulClientPrivateKeyLength = strlen( pcClientPrivateKey ) + 1;

    xParams.ulClientPrivateKeyType = ulClientPrivateKeyType;

    /* Provision using alternate cert and key. */
    vAlternateKeyProvisioning( &xParams );
}

/*-----------------------------------------------------------*/

static CK_RV prvInitializeAndStartSession( CK_FUNCTION_LIST_PTR * ppxFunctionList,
                                           CK_SLOT_ID * pxSlotId,
                                           CK_SESSION_HANDLE * pxSession )
{
    CK_RV xResult = 0;
    CK_C_GetFunctionList pxCkGetFunctionList = NULL;
    CK_ULONG ulCount = 1;

    /* Ensure that the PKCS#11 module is initialized. */
    if( 0 == xResult )
    {
        pxCkGetFunctionList = C_GetFunctionList;
        xResult = pxCkGetFunctionList( ppxFunctionList );
    }

    if( 0 == xResult )
    {
        xResult = ( *ppxFunctionList )->C_Initialize( NULL );
    }

    /* Get the default private key storage ID. */
    if( 0 == xResult )
    {
        xResult = ( *ppxFunctionList )->C_GetSlotList(
            CK_TRUE,
            pxSlotId,
            &ulCount );
    }

    /* Start a private session with the PKCS#11 module. */
    if( 0 == xResult )
    {
        xResult = ( *ppxFunctionList )->C_OpenSession(
            *pxSlotId,
            0,
            NULL,
            NULL,
            pxSession );
    }

    return xResult;
}

/*-----------------------------------------------------------*/

static CK_RV prvImportPublicKey( CK_SESSION_HANDLE xSession,
                                 CK_FUNCTION_LIST_PTR pxFunctionList,
                                 CK_OBJECT_HANDLE_PTR pxPublicKeyHandle,
                                 const char * const pcPublicKey )
{
    CK_RV xResult = 0;
    CK_OBJECT_CLASS xPublicKeyClass = CKO_PUBLIC_KEY;

    /* It doesn't matter what key type is passed. The key type will be automatically
     * identified. */
    CK_KEY_TYPE xKeyType = CKK_RSA;

    /* Public key configuration template. */
    CK_ATTRIBUTE xPublicKeyTemplate[] =
    {
        { CKA_CLASS,    &xPublicKeyClass, sizeof( xPublicKeyClass ) },
        { CKA_KEY_TYPE, &xKeyType,        sizeof( xKeyType )        },
        { CKA_VALUE,
          ( CK_VOID_PTR ) pcPublicKey,
          ( CK_ULONG ) strlen( pcPublicKey ) + 1 }
    };

    /* Create an object using the public key. */
    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_CreateObject(
            xSession,
            xPublicKeyTemplate,
            sizeof( xPublicKeyTemplate ) / sizeof( CK_ATTRIBUTE ),
            pxPublicKeyHandle
            );
    }

    return xResult;
}

/*-----------------------------------------------------------*/

static CK_RV prvImportCertificateAndKeys( const char * const pcCertificate,
                                          const char * const pcPrivateKey,
                                          const char * const pcPublicKey,
                                          CK_KEY_TYPE xKeyType )
{
    CK_RV xResult = 0;
    CK_FUNCTION_LIST_PTR pxFunctionList = NULL;
    CK_SLOT_ID xSlotId = 0;
    CK_SESSION_HANDLE xSession = 0;
    CK_OBJECT_HANDLE xObject = 0;

    /* Certificate configuration template. */
    CK_OBJECT_CLASS xCertificateClass = CKO_CERTIFICATE;
    CK_OBJECT_CLASS xCertificateType = pkcs11CERTIFICATE_TYPE_USER;
    CK_ATTRIBUTE xCertificateTemplate[] =
    {
        { CKA_CLASS,            &xCertificateClass, sizeof( xCertificateClass ) },
        { CKA_VALUE,
          ( CK_VOID_PTR ) pcCertificate,
          ( CK_ULONG ) strlen( pcCertificate ) + 1 },
        { CKA_CERTIFICATE_TYPE, &xCertificateType,  sizeof( xCertificateType )  }
    };

    /* Private key configuration template. */
    CK_OBJECT_CLASS xPrivateKeyClass = CKO_PRIVATE_KEY;
    CK_BBOOL xCanSign = CK_TRUE;
    CK_ATTRIBUTE xPrivateKeyTemplate[] =
    {
        { CKA_CLASS,    &xPrivateKeyClass, sizeof( xPrivateKeyClass ) },
        { CKA_KEY_TYPE, &xKeyType,         sizeof( xKeyType )         },
        { CKA_SIGN,     &xCanSign,         sizeof( xCanSign )         },
        { CKA_VALUE,
          ( CK_VOID_PTR ) pcPrivateKey,
          ( CK_ULONG ) strlen( pcPrivateKey ) + 1 }
    };

    /* Initialize the module and start a private session. */
    xResult = prvInitializeAndStartSession(
        &pxFunctionList,
        &xSlotId,
        &xSession );

    /** \brief Check that a certificate and private key can be imported into
     * persistent storage.
     *  @{
     */

    /* Create an object using the encoded private key. */
    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_CreateObject(
            xSession,
            xPrivateKeyTemplate,
            sizeof( xPrivateKeyTemplate ) / sizeof( CK_ATTRIBUTE ),
            &xObject );
    }

    /* Free the private key. */
    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_DestroyObject(
            xSession,
            xObject );
        xObject = 0;
    }

    /* Create an object using the encoded certificate. */
    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_CreateObject(
            xSession,
            xCertificateTemplate,
            sizeof( xCertificateTemplate ) / sizeof( CK_ATTRIBUTE ),
            &xObject );
    }

    /* Free the certificate. */
    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_DestroyObject(
            xSession,
            xObject );
        xObject = 0;
    }

    /* Import a public key. */
    if( 0 == xResult )
    {
        xResult = prvImportPublicKey( xSession,
                                      pxFunctionList,
                                      &xObject,
                                      pcPublicKey );
    }

    /* Free the public key. */
    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_DestroyObject(
            xSession,
            xObject );
        xObject = 0;
    }

    /* Cleanup PKCS#11. */
    if( ( NULL != pxFunctionList ) &&
        ( NULL != pxFunctionList->C_CloseSession ) )
    {
        pxFunctionList->C_CloseSession( xSession );
        pxFunctionList->C_Finalize( NULL );
    }

    return xResult;
    /** @}*/
}

/*-----------------------------------------------------------*/

static CK_RV prvExportCertificateAndKeys( const char * const pcCertificate,
                                          const char * const pcPrivateKey,
                                          const char * const pcPublicKey,
                                          CK_KEY_TYPE xKeyType )
{
    CK_RV xResult;
    CK_FUNCTION_LIST_PTR pxFunctionList = NULL;
    CK_SLOT_ID xSlotId = 0;
    CK_SESSION_HANDLE xSession = 0;
    CK_ATTRIBUTE xTemplate = { 0 };
    CK_ULONG ulCount = 0;
    CK_OBJECT_CLASS xObjClass = 0;
    CK_OBJECT_HANDLE xCertificateHandle = 0;
    CK_OBJECT_HANDLE xPublicKeyHandle = 0;
    CK_OBJECT_HANDLE xPrivateKeyHandle = 0;
    CK_BYTE_PTR pucExportBuffer = NULL;
#ifdef MBEDTLS
    mbedtls_x509_crt xCertContext = { 0 };
#endif
    /* Reprovision with given certificate and key. */
    prvReprovision( pcCertificate, pcPrivateKey, xKeyType );

    /* Initialize the module and start a private session. */
    xResult = prvInitializeAndStartSession(
        &pxFunctionList,
        &xSlotId,
        &xSession );

    /* Import a public key. */
    if( 0 == xResult )
    {
        xResult = prvImportPublicKey( xSession,
                                      pxFunctionList,
                                      &xPublicKeyHandle,
                                      pcPublicKey );
    }

    /* Get the handle of the certificate. */
    if( 0 == xResult )
    {
        xObjClass = CKO_CERTIFICATE;
        xTemplate.type = CKA_CLASS;
        xTemplate.ulValueLen = sizeof( CKA_CLASS );
        xTemplate.pValue = &xObjClass;

        xResult = pxFunctionList->C_FindObjectsInit(
            xSession, &xTemplate, 1 );
    }

    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_FindObjects( xSession,
                                                 &xCertificateHandle,
                                                 1,
                                                 &ulCount );
    }

    /* Get the handle of the private key. */
    if( 0 == xResult )
    {
        xObjClass = CKO_PRIVATE_KEY;
        xTemplate.type = CKA_CLASS;
        xTemplate.ulValueLen = sizeof( CKA_CLASS );
        xTemplate.pValue = &xObjClass;

        xResult = pxFunctionList->C_FindObjectsInit(
            xSession, &xTemplate, 1 );
    }

    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_FindObjects( xSession,
                                                 &xPrivateKeyHandle,
                                                 1,
                                                 &ulCount );
    }

    /* Close the FindObjects context. */
    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_FindObjectsFinal( xSession );
    }

    /* Attempt to export the private key. This should fail. */
    if( 0 == xResult )
    {
        xTemplate.type = CKA_VALUE;
        xTemplate.pValue = NULL;

        if( 0 == pxFunctionList->C_GetAttributeValue( xSession,
                                                      xPrivateKeyHandle,
                                                      &xTemplate,
                                                      1 ) )
        {
            xResult = CKR_FUNCTION_FAILED;
        }
        else
        {
            xResult = CKR_OK;
        }
    }

    /* Test certificate export. */
    if( 0 == xResult )
    {
        xTemplate.pValue = NULL;
        xResult = pxFunctionList->C_GetAttributeValue(
            xSession,
            xCertificateHandle,
            &xTemplate, 1 );
    }

    if( 0 == xResult )
    {
        pucExportBuffer = ( CK_BYTE_PTR ) pvPortMalloc(
            xTemplate.ulValueLen );

        if( NULL == pucExportBuffer )
        {
            xResult = CKR_HOST_MEMORY;
        }
    }

    if( 0 == xResult )
    {
        xTemplate.pValue = pucExportBuffer;
        xResult = pxFunctionList->C_GetAttributeValue(
            xSession,
            xCertificateHandle,
            &xTemplate, 1 );
    }

    /* Compare the exported certificate with the provisioned certificate. They
     * should be the same. */
    if( 0 == xResult )
    {
    #ifdef MBEDTLS
        mbedtls_x509_crt_init( &xCertContext );

        if( 0 == mbedtls_x509_crt_parse( &xCertContext,
                                         ( const uint8_t * ) pcCertificate,
                                         strlen( pcCertificate ) + 1 ) )
        {
            if( ( xCertContext.raw.len != xTemplate.ulValueLen ) ||
                ( 0 != memcmp( xCertContext.raw.p,
                               xTemplate.pValue,
                               xTemplate.ulValueLen ) ) )
            {
                xResult = CKR_FUNCTION_FAILED;
            }

            mbedtls_x509_crt_free( &xCertContext );
        }
        else
        {
            xResult = CKR_HOST_MEMORY;
        }
 #endif       
    }

    /* Free the exported certificate. */
    if( NULL != pucExportBuffer )
    {
        vPortFree( pucExportBuffer );
        pucExportBuffer = NULL;
    }

    /* Clear the template values being used for the certificate. */
    memset( &xTemplate, 0x00, sizeof( xTemplate ) );

    /* Test public key export. */
    if( 0 == xResult )
    {
        xTemplate.type = CKA_VALUE;
        xResult = pxFunctionList->C_GetAttributeValue(
            xSession,
            xPublicKeyHandle,
            &xTemplate, 1 );
    }

    if( 0 == xResult )
    {
        pucExportBuffer = ( CK_BYTE_PTR ) pvPortMalloc(
            xTemplate.ulValueLen );

        if( NULL == pucExportBuffer )
        {
            xResult = CKR_HOST_MEMORY;
        }
    }

    if( 0 == xResult )
    {
        xTemplate.pValue = pucExportBuffer;
        xResult = pxFunctionList->C_GetAttributeValue(
            xSession,
            xPublicKeyHandle,
            &xTemplate, 1 );
    }

    /* Free the exported public key. */
    if( NULL != pucExportBuffer )
    {
        vPortFree( pucExportBuffer );
        pucExportBuffer = NULL;
    }

    /* Free the public key object. */
    if( 0 != xPublicKeyHandle )
    {
        xResult = pxFunctionList->C_DestroyObject(
            xSession,
            xPublicKeyHandle );
        xPublicKeyHandle = 0;
    }

    if( ( NULL != pxFunctionList ) &&
        ( NULL != pxFunctionList->C_CloseSession ) )
    {
        pxFunctionList->C_CloseSession( xSession );
        pxFunctionList->C_Finalize( NULL );
    }

    return xResult;
}

/*-----------------------------------------------------------*/
static CK_RV prvSha256Digest(CK_FUNCTION_LIST_PTR pxFunctionList,
                                CK_SESSION_HANDLE  xSession,
                                CK_BYTE_PTR pucMessage,
                                CK_ULONG ulMsgLen,
                                CK_BYTE_PTR pucHash)
{
    CK_RV xResult = 0;
    CK_MECHANISM xMechanism;
    CK_ULONG ulHashLen = pcks11SHA256_DIGEST_LENGTH; 
    xMechanism.mechanism = CKM_SHA256;
    xResult =  pxFunctionList->C_DigestInit(xSession,&xMechanism);
    if(0 == xResult)
    {
        xResult =  pxFunctionList->C_DigestUpdate(xSession,pucMessage,ulMsgLen);
    }
    if(0 == xResult)
    {
        xResult =  pxFunctionList->C_DigestFinal(xSession,pucHash,&ulHashLen);
    }
    return xResult;
}
static int32_t qcom_crypto_sha256(CK_BYTE_PTR pucMessage, CK_ULONG ulMsgLen,
                    CK_BYTE_PTR pucHash,CK_ULONG_PTR pulHashLen)
{
    qapi_Crypto_Op_Hdl_t opHdl;
    if (qapi_Crypto_Op_Alloc(QAPI_CRYPTO_ALG_SHA256_E, QAPI_CRYPTO_MODE_DIGEST_E, 0, &opHdl) != QAPI_OK) {
        configPRINTF(("\nFailed to alloc op\n"));
    }
#if 0
    if (qapi_Crypto_Op_Digest_Update(opHdl, pucMessage, 32) != QAPI_OK) {
        configPRINTF(("\nFailed to digest update\n"));
    }
    if (qapi_Crypto_Op_Digest_Update(opHdl, pucMessage, 64) != QAPI_OK) {
        configPRINTF(("\nFailed to digest update\n"));
    }
#endif
    if (qapi_Crypto_Op_Digest_Final(opHdl, (void*)pucMessage, ulMsgLen, pucHash, pulHashLen) != QAPI_OK)
    {
        configPRINTF(("\nFailed to digest dofinal\n"));
    }
    qapi_Crypto_Op_Free(opHdl);
}

/* To use a public key for verification, pass a pointer to it. Otherwise, pass NULL. */
static CK_RV prvSignVerifyRoundTrip( CK_MECHANISM_TYPE xMechanism,
                                     const char * const pcPublicKey )
{
    CK_RV xResult = 0;
    CK_FUNCTION_LIST_PTR pxFunctionList = NULL;
    CK_SLOT_ID xSlotId = 0;
    CK_SESSION_HANDLE xSession = 0;
    CK_ULONG ulCount = 0;
    CK_ATTRIBUTE xTemplate = { 0 };
    CK_OBJECT_CLASS xObjClass = 0;
    CK_OBJECT_HANDLE xPrivateKey = 0;
    CK_OBJECT_HANDLE xVerifyInitKeyHandle = 0;
    CK_ULONG ulKeyType = 0;
    CK_MECHANISM xMech = { 0 };
    CK_BYTE pucMessage[ cryptoSHA256_DIGEST_BYTES ] = { 0 };
    CK_BYTE pucHash[ cryptoSHA256_DIGEST_BYTES ] = { 0 };
    CK_BYTE pucSignature[ 256 ] = { 0 };
    CK_OBJECT_HANDLE xPublicKey = 0;

    /* Hash the message (the null input). */
#ifdef MBEDTLS
    ( void ) mbedtls_sha256_ret( pucMessage, 0, pucHash, 0 );
#else
{
    uint32_t hashLen = cryptoSHA256_DIGEST_BYTES;
    qcom_crypto_sha256(pucMessage,cryptoSHA256_DIGEST_BYTES,pucHash,&hashLen);
}
#endif
    /* Initialize the module and start a private session. */
    xResult = prvInitializeAndStartSession(
        &pxFunctionList,
        &xSlotId,
        &xSession );

    /* Get the (first) private key handle. */
    if( 0 == xResult )
    {
        xTemplate.type = CKA_CLASS;
        xTemplate.ulValueLen = sizeof( CKA_CLASS );
        xTemplate.pValue = &xObjClass;
        xObjClass = CKO_PRIVATE_KEY;
        xResult = pxFunctionList->C_FindObjectsInit(
            xSession, &xTemplate, 1 );
    }

    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_FindObjects(
            xSession,
            &xPrivateKey,
            1,
            &ulCount );
    }

    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_FindObjectsFinal( xSession );
    }

    /* Query the key type. */
    if( 0 == xResult )
    {
        xTemplate.type = CKA_KEY_TYPE;
        xTemplate.ulValueLen = sizeof( ulKeyType );
        xTemplate.pValue = &ulKeyType;
        xResult = pxFunctionList->C_GetAttributeValue(
            xSession,
            xPrivateKey,
            &xTemplate,
            1 );
    }

    /* Sign a hash. */
    if( 0 == xResult )
    {
        xMech.mechanism = xMechanism;
        xResult = pxFunctionList->C_SignInit(
            xSession,
            &xMech,
            xPrivateKey );
    }

    if( 0 == xResult )
    {
        /* TODO - query the key size instead. */
        ulCount = sizeof( pucSignature );
        xResult = pxFunctionList->C_Sign(
            xSession,
            pucHash,
            sizeof( pucHash ),
            pucSignature,
            &ulCount );
    }

    /* Create an object using the public key if provided. */
    if( ( 0 == xResult ) && ( pcPublicKey != NULL ) )
    {
        xResult = prvImportPublicKey( xSession,
                                      pxFunctionList,
                                      &xPublicKey,
                                      pcPublicKey );
    }

    /* Verify the signature using the same key handle. */
    if( 0 == xResult )
    {
        /* If a public key was given, use it. */
        if( pcPublicKey != NULL )
        {
            xVerifyInitKeyHandle = xPublicKey;
        }
        else
        {
            xVerifyInitKeyHandle = xPrivateKey;
        }

        xResult = pxFunctionList->C_VerifyInit(
            xSession,
            &xMech,
            xVerifyInitKeyHandle );
    }

    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_Verify(
            xSession,
            pucHash,
            sizeof( pucHash ),
            pucSignature,
            ulCount );
    }

    /* Clean-up. */
    if( ( NULL != pxFunctionList ) &&
        ( NULL != pxFunctionList->C_CloseSession ) )
    {
        pxFunctionList->C_CloseSession( xSession );
        pxFunctionList->C_Finalize( NULL );
    }

    return xResult;
}

/*-----------------------------------------------------------*/

static void prvSignVerifyTask( void * pvParameters )
{
    SignVerifyTaskParams_t * pxTaskParams;
    BaseType_t i;
    CK_RV xTestResult = 0;

    pxTaskParams = ( SignVerifyTaskParams_t * ) pvParameters;

    /* Repeatedly run sign-verify in a loop. */
    for( i = 0; i < pkcs11testSIGN_VERIFY_LOOP_COUNT; i++ )
    {
        xTestResult |= prvSignVerifyRoundTrip( CKM_SHA256_RSA_PKCS, NULL );

        if( xTestResult != 0 )
        {
            configPRINTF( ( "Task %d: SignVerify error in loop iteration %d.\r\n",
                            pxTaskParams->xTaskNumber,
                            i ) );
            break;
        }
    }

    /* Report the result of the sign-verify loop. */
    pxTaskParams->xTestResult = xTestResult;

    /* Report that task is finished, then delete task. */
    ( void ) xEventGroupSetBits( xSyncEventGroup,
                                 ( 1 << pxTaskParams->xTaskNumber ) );
    vTaskDelete( NULL );
}

/*-----------------------------------------------------------*/

TEST_GROUP( Full_PKCS11 );

TEST_SETUP( Full_PKCS11 )
{
}

TEST_TEAR_DOWN( Full_PKCS11 )
{
}

TEST_GROUP_RUNNER( Full_PKCS11 )
{
    /* Test PKCS11 functions with invalid parameters. */
    RUN_TEST_CASE( Full_PKCS11, GetFunctionListInvalidParams );
    RUN_TEST_CASE( Full_PKCS11, InitializeFinalizeInvalidParams );
    RUN_TEST_CASE( Full_PKCS11, GetSlotListInvalidParams );
    RUN_TEST_CASE( Full_PKCS11, OpenCloseSessionInvalidParams );

    /* Verify related tests. */
    RUN_TEST_CASE( Full_PKCS11, C_PKCSHappyTestVerify );
    RUN_TEST_CASE( Full_PKCS11, C_PKCSC_VerifyInvalidParams );
    RUN_TEST_CASE( Full_PKCS11, C_PKCSC_VerifyInitInvalidParams );

    /* Sign related tests. */
    RUN_TEST_CASE( Full_PKCS11, C_PKCSHappyTestSign );
    RUN_TEST_CASE( Full_PKCS11, C_PKCSSignInvalidParams );
    RUN_TEST_CASE( Full_PKCS11, C_PKCSSignInitInvalidParams );

    /* Object related tests. */
    RUN_TEST_CASE( Full_PKCS11, C_PKCSHappyTestObject );
    RUN_TEST_CASE( Full_PKCS11, C_PKCSCreateObjectInvalidParameters );
    RUN_TEST_CASE( Full_PKCS11, C_PKCSFindObjectsFinalInvalidParams );
    RUN_TEST_CASE( Full_PKCS11, C_PKCSFindObjectsInvalidParams );
    RUN_TEST_CASE( Full_PKCS11, C_PKCSFindObjectsInitInvalidParams );
    RUN_TEST_CASE( Full_PKCS11, C_PKCSGetAttributeValueInvalidParams );

    /* Generated Random tests. */
    RUN_TEST_CASE( Full_PKCS11, C_PKCSGenerateRandomInvalidParameters );
    RUN_TEST_CASE( Full_PKCS11, C_PKCSGenerateRandomTestHappyTest );

    /* Test that keys can be parsed. */
    RUN_TEST_CASE( Full_PKCS11, TestRSAParse );
    RUN_TEST_CASE( Full_PKCS11, TestECDSAParse );

    /* Test key and cert export. */
    RUN_TEST_CASE( Full_PKCS11, TestRSAExport );
    RUN_TEST_CASE( Full_PKCS11, TestECDSAExport );

    /* Basic sign-verify tests using RSA/SHA256 mechanism. */
    RUN_TEST_CASE( Full_PKCS11, SignVerifyRoundTripRSANoPubKey );
    RUN_TEST_CASE( Full_PKCS11, SignVerifyRoundTripWithCorrectRSAPublicKey );
    RUN_TEST_CASE( Full_PKCS11, SignVerifyRoundTripWithWrongRSAPublicKey );

    /* Basic sign-verify tests using EC/SHA256 mechanism. */
    RUN_TEST_CASE( Full_PKCS11, SignVerifyRoundTripECNoPubKey );
    RUN_TEST_CASE( Full_PKCS11, SignVerifyRoundTripWithCorrectECPublicKey );
    RUN_TEST_CASE( Full_PKCS11, SignVerifyRoundTripWithWrongECPublicKey );

    /* Test signature verification with output from OpenSSL. Also attempts to
     * verify an invalid signature. */
    RUN_TEST_CASE( Full_PKCS11, SignVerifyCryptoApiInteropRSA );

    /* Run sign-verify in a loop with multiple tasks. This test may take a while. */
    RUN_TEST_CASE( Full_PKCS11, SignVerifyRoundTrip_MultitaskLoop );

    /* Re-provision the device with default RSA certs so that subsequent tests are not changed. */
    vDevModeKeyProvisioning();
}

TEST( Full_PKCS11, C_PKCSC_VerifyInvalidParams )
{
    CK_RV xResult = 0;
    CK_FUNCTION_LIST_PTR pxFunctionList = NULL;
    CK_SLOT_ID xSlotId = 0;
    CK_SESSION_HANDLE xSession = 0;
    CK_MECHANISM xMech = { 0 };
    CK_OBJECT_HANDLE xPublicKey = 0;

    /* Reprovision with test RSA certificate and private key. */
    prvReprovision( pcValidRSACertificate, pcValidRSAPrivateKey, CKK_RSA );

    /* Initialize the module and start a private session. */
    xResult = prvInitializeAndStartSession(
        &pxFunctionList,
        &xSlotId,
        &xSession );

    if( 0 != xResult )
    {
        configPRINTF( ( "Could not start session.\r\n" ) );
    }

    if( 0 == xResult )
    {
        xResult = prvImportPublicKey( xSession,
                                      pxFunctionList,
                                      &xPublicKey,
                                      pcValidRSAPublicKey );

        if( 0 != xResult )
        {
            configPRINTF( ( "Failed to import public key.\r\n" ) );
        }
    }

    /* Verify the signature using the same key handle. */
    if( 0 == xResult )
    {
        xMech.mechanism = CKM_SHA256_RSA_PKCS;
        xResult = pxFunctionList->C_VerifyInit(
            xSession,
            &xMech,
            xPublicKey );

        if( 0 != xResult )
        {
            configPRINTF( ( "Failed to initialize signature verification.\r\n" ) );
        }
    }

    if( 0 == xResult )
    {
        if( TEST_PROTECT() )
        {
            xResult = pxFunctionList->C_Verify(
                xSession,
                ( CK_BYTE_PTR ) NULL,
                ( CK_ULONG ) sizeof( pcEmptyStringHash ),
                ( CK_BYTE_PTR ) pcSignedData,
                ( CK_ULONG ) sizeof( pcSignedData ) );
            TEST_ASSERT_EQUAL_INT32_MESSAGE( xResult, CKR_ARGUMENTS_BAD, "Unexpected status from C_PKCSC_VerifyInitInvalidParams" );

            xResult = pxFunctionList->C_Verify(
                xSession,
                ( CK_BYTE_PTR ) pcEmptyStringHash,
                ( CK_ULONG ) sizeof( pcEmptyStringHash ),
                NULL,
                ( CK_ULONG ) sizeof( pcSignedData ) );
            TEST_ASSERT_EQUAL_INT32_MESSAGE( xResult, CKR_ARGUMENTS_BAD, "Unexpected status from C_PKCSC_VerifyInitInvalidParams" );

            xResult = pxFunctionList->C_Verify(
                xSession,
                ( CK_BYTE_PTR ) pcEmptyStringHash,
                ( CK_ULONG ) sizeof( pcEmptyStringHash ),
                ( CK_BYTE_PTR ) pcSignedData,
                ( CK_ULONG ) 0 );
            TEST_ASSERT_EQUAL_INT32_MESSAGE( xResult, CKR_SIGNATURE_INVALID, "Unexpected status from C_PKCSC_VerifyInitInvalidParams" );

            xResult = 0;
        }
    }

    /* Cleanup PKCS#11. */
    if( NULL != pxFunctionList )
    {
        ( void ) pxFunctionList->C_CloseSession( xSession );
        ( void ) pxFunctionList->C_Finalize( NULL );
    }

    TEST_ASSERT_EQUAL_INT32( 0, xResult );
}

TEST( Full_PKCS11, C_PKCSC_VerifyInitInvalidParams )
{
    CK_RV xResult = 0;
    CK_FUNCTION_LIST_PTR pxFunctionList = NULL;
    CK_SLOT_ID xSlotId = 0;
    CK_SESSION_HANDLE xSession = 0;
    CK_OBJECT_HANDLE xPublicKey = 0;


    /* Reprovision with test RSA certificate and private key. */
    prvReprovision( pcValidRSACertificate, pcValidRSAPrivateKey, CKK_RSA );

    /* Initialize the module and start a private session. */
    xResult = prvInitializeAndStartSession(
        &pxFunctionList,
        &xSlotId,
        &xSession );

    if( 0 != xResult )
    {
        configPRINTF( ( "Could not start session.\r\n" ) );
    }

    if( 0 == xResult )
    {
        xResult = prvImportPublicKey( xSession,
                                      pxFunctionList,
                                      &xPublicKey,
                                      pcValidRSAPublicKey );

        if( 0 != xResult )
        {
            configPRINTF( ( "Failed to import public key.\r\n" ) );
        }
    }

    /* Verify the signature using the same key handle. */
    if( 0 == xResult )
    {
        if( TEST_PROTECT() )
        {
            xResult = pxFunctionList->C_VerifyInit(
                xSession,
                NULL,
                xPublicKey );
            TEST_ASSERT_EQUAL_INT32_MESSAGE( xResult, CKR_ARGUMENTS_BAD, "Unexpected status from C_PKCSC_VerifyInitInvalidParams" );

            xResult = 0;
        }
    }

    /* Cleanup PKCS#11. */
    if( NULL != pxFunctionList )
    {
        ( void ) pxFunctionList->C_CloseSession( xSession );
        ( void ) pxFunctionList->C_Finalize( NULL );
    }

    TEST_ASSERT_EQUAL_INT32( 0, xResult );
}

TEST( Full_PKCS11, C_PKCSSignInvalidParams )
{
    CK_RV xResult = 0;
    CK_FUNCTION_LIST_PTR pxFunctionList = NULL;
    CK_SLOT_ID xSlotId = 0;
    CK_SESSION_HANDLE xSession = 0;
    CK_ULONG ulCount = 0;
    CK_ATTRIBUTE xTemplate = { 0 };
    CK_OBJECT_CLASS xObjClass = 0;
    CK_OBJECT_HANDLE xPrivateKey = 0;
    CK_ULONG ulKeyType = 0;
    CK_MECHANISM xMech = { 0 };
    CK_BYTE pucMessage[ cryptoSHA256_DIGEST_BYTES ] = { 0 };
    CK_BYTE pucHash[ cryptoSHA256_DIGEST_BYTES ] = { 0 };
    CK_BYTE pucSignature[ 256 ] = { 0 };

    prvReprovision( pcValidRSACertificate, pcValidRSAPrivateKey, CKK_RSA );

    /* Hash the message (the null input). */
#ifdef MBEDTLS
    ( void ) mbedtls_sha256_ret( pucMessage, 0, pucHash, 0 );
#else
{
    uint32_t hashLen = cryptoSHA256_DIGEST_BYTES;
    qcom_crypto_sha256(pucMessage,cryptoSHA256_DIGEST_BYTES,pucHash,&hashLen);
}
#endif

    /* Initialize the module and start a private session. */
    xResult = prvInitializeAndStartSession(
        &pxFunctionList,
        &xSlotId,
        &xSession );

    /* Get the (first) private key handle. */
    if( 0 == xResult )
    {
        xTemplate.type = CKA_CLASS;
        xTemplate.ulValueLen = sizeof( CKA_CLASS );
        xTemplate.pValue = &xObjClass;
        xObjClass = CKO_PRIVATE_KEY;
        xResult = pxFunctionList->C_FindObjectsInit(
            xSession, &xTemplate, 1 );
    }

    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_FindObjects(
            xSession,
            &xPrivateKey,
            1,
            &ulCount );
    }

    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_FindObjectsFinal( xSession );
    }

    /* Query the key type. */
    if( 0 == xResult )
    {
        xTemplate.type = CKA_KEY_TYPE;
        xTemplate.ulValueLen = sizeof( ulKeyType );
        xTemplate.pValue = &ulKeyType;
        xResult = pxFunctionList->C_GetAttributeValue(
            xSession,
            xPrivateKey,
            &xTemplate,
            1 );
    }

    /* Sign a hash. */
    if( 0 == xResult )
    {
        xMech.mechanism = CKM_SHA256_RSA_PKCS;
        xResult = pxFunctionList->C_SignInit(
            xSession,
            &xMech,
            xPrivateKey );
    }

    if( 0 == xResult )
    {
        if( TEST_PROTECT() )
        {
            ulCount = sizeof( pucSignature );
            xResult = pxFunctionList->C_Sign(
                xSession,
                pucHash,
                0,
                pucSignature,
                &ulCount );
            TEST_ASSERT_EQUAL_INT32_MESSAGE( xResult, CKR_DATA_LEN_RANGE, "Unexpected status from C_Sign" );

            xResult = pxFunctionList->C_Sign(
                xSession,
                pucHash,
                sizeof( pucHash ),
                pucSignature,
                NULL );
            TEST_ASSERT_EQUAL_INT32_MESSAGE( xResult, CKR_ARGUMENTS_BAD, "Unexpected status from C_Sign" );

            xResult = 0;
        }
    }

    /* Clean-up. */
    if( NULL != pxFunctionList )
    {
        ( void ) pxFunctionList->C_CloseSession( xSession );
        ( void ) pxFunctionList->C_Finalize( NULL );
    }

    TEST_ASSERT_EQUAL_INT32( 0, xResult );
}


TEST( Full_PKCS11, C_PKCSSignInitInvalidParams )
{
    CK_RV xResult = 0;
    CK_FUNCTION_LIST_PTR pxFunctionList = NULL;
    CK_SLOT_ID xSlotId = 0;
    CK_SESSION_HANDLE xSession = 0;
    CK_ULONG ulCount = 0;
    CK_ATTRIBUTE xTemplate = { 0 };
    CK_OBJECT_CLASS xObjClass = 0;
    CK_OBJECT_HANDLE xPrivateKey = 0;
    CK_ULONG ulKeyType = 0;
    CK_BYTE pucMessage[ cryptoSHA256_DIGEST_BYTES ] = { 0 };
    CK_BYTE pucHash[ cryptoSHA256_DIGEST_BYTES ] = { 0 };

    prvReprovision( pcValidRSACertificate, pcValidRSAPrivateKey, CKK_RSA );

    /* Hash the message (the null input). */
    #ifdef MBEDTLS
    ( void ) mbedtls_sha256_ret( pucMessage, 0, pucHash, 0 );
#else
{
    uint32_t hashLen = cryptoSHA256_DIGEST_BYTES;
    qcom_crypto_sha256(pucMessage,cryptoSHA256_DIGEST_BYTES,pucHash,&hashLen);
}
#endif

    /* Initialize the module and start a private session. */
    xResult = prvInitializeAndStartSession(
        &pxFunctionList,
        &xSlotId,
        &xSession );

    /* Get the (first) private key handle. */
    if( 0 == xResult )
    {
        xTemplate.type = CKA_CLASS;
        xTemplate.ulValueLen = sizeof( CKA_CLASS );
        xTemplate.pValue = &xObjClass;
        xObjClass = CKO_PRIVATE_KEY;
        xResult = pxFunctionList->C_FindObjectsInit(
            xSession, &xTemplate, 1 );
    }

    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_FindObjects(
            xSession,
            &xPrivateKey,
            1,
            &ulCount );
    }

    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_FindObjectsFinal( xSession );
    }

    /* Query the key type. */
    if( 0 == xResult )
    {
        xTemplate.type = CKA_KEY_TYPE;
        xTemplate.ulValueLen = sizeof( ulKeyType );
        xTemplate.pValue = &ulKeyType;
        xResult = pxFunctionList->C_GetAttributeValue(
            xSession,
            xPrivateKey,
            &xTemplate,
            1 );
    }

    /* Sign a hash. */
    if( 0 == xResult )
    {
        if( TEST_PROTECT() )
        {
            xResult = pxFunctionList->C_SignInit(
                xSession,
                NULL,
                xPrivateKey );
            TEST_ASSERT_EQUAL_INT32_MESSAGE( xResult, CKR_ARGUMENTS_BAD, "Unexpected status from C_SignInit" );

            xResult = 0;
        }
    }

    /* Clean-up. */
    if( NULL != pxFunctionList )
    {
        ( void ) pxFunctionList->C_CloseSession( xSession );
        ( void ) pxFunctionList->C_Finalize( NULL );
    }

    TEST_ASSERT_EQUAL_INT32( 0, xResult );
}

TEST( Full_PKCS11, C_PKCSFindObjectsFinalInvalidParams )
{
    CK_RV xResult = 0;
    CK_OBJECT_CLASS xPublicKeyClass = CKO_PUBLIC_KEY;
    CK_FUNCTION_LIST_PTR pxFunctionList = NULL;
    CK_SLOT_ID xSlotId = 0;
    CK_SESSION_HANDLE xSession = 0;
    CK_OBJECT_HANDLE xObject = 0;
    CK_BBOOL xObjCreated = CK_FALSE;
    CK_ATTRIBUTE xTemplate = { 0 };
    CK_OBJECT_CLASS xObjClass = 0;
    CK_OBJECT_HANDLE xCertObj = 0;
    CK_ULONG ulCount = 0;

    /* It doesn't matter what key type is passed. The key type will be automatically
     * identified. */
    CK_KEY_TYPE xKeyType = CKK_RSA;

    /* Public key configuration template. */
    CK_ATTRIBUTE xPublicKeyTemplate[] =
    {
        { CKA_CLASS,    &xPublicKeyClass, sizeof( xPublicKeyClass ) },
        { CKA_KEY_TYPE, &xKeyType,        sizeof( xKeyType )        },
        { CKA_VALUE,
          ( CK_VOID_PTR ) pcValidRSAPublicKey,
          ( CK_ULONG ) strlen( pcValidRSAPublicKey ) + 1 }
    };

    /* Reprovision with test RSA certificate and private key. */
    prvReprovision( pcValidRSACertificate, pcValidRSAPrivateKey, CKK_RSA );

    /* Initialize the module and start a private session. */
    xResult = prvInitializeAndStartSession(
        &pxFunctionList,
        &xSlotId,
        &xSession );

    if( 0 != xResult )
    {
        configPRINTF( ( "Could not start session.\r\n" ) );
    }

    /* Create an object using the public key. */
    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_CreateObject(
            xSession,
            xPublicKeyTemplate,
            sizeof( xPublicKeyTemplate ) / sizeof( CK_ATTRIBUTE ),
            &xObject
            );

        if( 0 != xResult )
        {
            configPRINTF( ( "Could not create object.\r\n" ) );
        }
        else
        {
            xObjCreated = CK_TRUE;
        }
    }

    /* Get the (first) certificate handle. */
    if( 0 == xResult )
    {
        if( TEST_PROTECT() )
        {
            xResult = pxFunctionList->C_FindObjectsFinal( xSession );
            TEST_ASSERT_EQUAL_INT32_MESSAGE( xResult, CKR_OPERATION_NOT_INITIALIZED, "Unexpected status from C_FindObjectsFinal" );

            /* Place holder for tests. */
            xResult = 0;
        }

        xTemplate.type = CKA_CLASS;
        xTemplate.ulValueLen = sizeof( CKA_CLASS );
        xTemplate.pValue = &xObjClass;
        xObjClass = CKO_CERTIFICATE;
        xResult = pxFunctionList->C_FindObjectsInit(
            xSession, &xTemplate, 1 );
    }

    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_FindObjects(
            xSession,
            &xCertObj,
            1,
            &ulCount );
    }

    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_FindObjectsFinal( xSession );
    }

    /* Free the public key. */
    if( xObjCreated == CK_TRUE )
    {
        xResult = pxFunctionList->C_DestroyObject(
            xSession,
            xObject );
        xObject = 0;

        if( 0 != xResult )
        {
            configPRINTF( ( "Could not destroy object.\r\n" ) );
        }
    }

    /* Cleanup PKCS#11. */
    if( NULL != pxFunctionList )
    {
        ( void ) pxFunctionList->C_CloseSession( xSession );
        ( void ) pxFunctionList->C_Finalize( NULL );
    }

    TEST_ASSERT_EQUAL_INT32( 0, xResult );
}

TEST( Full_PKCS11, C_PKCSFindObjectsInvalidParams )
{
    CK_RV xResult = 0;
    CK_OBJECT_CLASS xPublicKeyClass = CKO_PUBLIC_KEY;
    CK_FUNCTION_LIST_PTR pxFunctionList = NULL;
    CK_SLOT_ID xSlotId = 0;
    CK_SESSION_HANDLE xSession = 0;
    CK_OBJECT_HANDLE xObject = 0;
    CK_BBOOL xObjCreated = CK_FALSE;
    CK_ATTRIBUTE xTemplate = { 0 };
    CK_OBJECT_CLASS xObjClass = 0;
    CK_OBJECT_HANDLE xCertObj = 0;
    CK_ULONG ulCount = 0;

    /* It doesn't matter what key type is passed. The key type will be automatically
     * identified. */
    CK_KEY_TYPE xKeyType = CKK_RSA;

    /* Public key configuration template. */
    CK_ATTRIBUTE xPublicKeyTemplate[] =
    {
        { CKA_CLASS,    &xPublicKeyClass, sizeof( xPublicKeyClass ) },
        { CKA_KEY_TYPE, &xKeyType,        sizeof( xKeyType )        },
        { CKA_VALUE,
          ( CK_VOID_PTR ) pcValidRSAPublicKey,
          ( CK_ULONG ) strlen( pcValidRSAPublicKey ) + 1 }
    };

    /* Reprovision with test RSA certificate and private key. */
    prvReprovision( pcValidRSACertificate, pcValidRSAPrivateKey, CKK_RSA );

    /* Initialize the module and start a private session. */
    xResult = prvInitializeAndStartSession(
        &pxFunctionList,
        &xSlotId,
        &xSession );

    if( 0 != xResult )
    {
        configPRINTF( ( "Could not start session.\r\n" ) );
    }

    /* Create an object using the public key. */
    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_CreateObject(
            xSession,
            xPublicKeyTemplate,
            sizeof( xPublicKeyTemplate ) / sizeof( CK_ATTRIBUTE ),
            &xObject
            );

        if( 0 != xResult )
        {
            configPRINTF( ( "Could not create object.\r\n" ) );
        }
        else
        {
            xObjCreated = CK_TRUE;
        }
    }

    /* Get the (first) certificate handle. */
    if( 0 == xResult )
    {
        if( TEST_PROTECT() )
        {
            xResult = pxFunctionList->C_FindObjects(
                xSession,
                &xCertObj,
                1,
                &ulCount );
            TEST_ASSERT_EQUAL_INT32_MESSAGE( xResult, CKR_OPERATION_NOT_INITIALIZED, "Unexpected status from C_FindObjects" );

            xResult = 0;
        }

        xTemplate.type = CKA_CLASS;
        xTemplate.ulValueLen = sizeof( CKA_CLASS );
        xTemplate.pValue = &xObjClass;
        xObjClass = CKO_CERTIFICATE;
        xResult = pxFunctionList->C_FindObjectsInit(
            xSession, &xTemplate, 1 );
    }

    if( 0 == xResult )
    {
        if( TEST_PROTECT() )
        {
            xResult = pxFunctionList->C_FindObjects(
                xSession,
                &xCertObj,
                0,
                &ulCount );
            TEST_ASSERT_EQUAL_INT32_MESSAGE( xResult, CKR_ARGUMENTS_BAD, "Unexpected status from C_FindObjects" );

            xResult = pxFunctionList->C_FindObjects(
                xSession,
                NULL,
                1,
                &ulCount );
            TEST_ASSERT_EQUAL_INT32_MESSAGE( xResult, CKR_ARGUMENTS_BAD, "Unexpected status from C_FindObjects" );

            xResult = pxFunctionList->C_FindObjects(
                xSession,
                &xCertObj,
                1,
                NULL );
            TEST_ASSERT_EQUAL_INT32_MESSAGE( xResult, CKR_ARGUMENTS_BAD, "Unexpected status from C_FindObjects" );
        }

        xResult = pxFunctionList->C_FindObjectsFinal( xSession );
    }

    /* Free the public key. */
    if( xObjCreated == CK_TRUE )
    {
        xResult = pxFunctionList->C_DestroyObject(
            xSession,
            xObject );
        xObject = 0;

        if( 0 != xResult )
        {
            configPRINTF( ( "Could not destroy object.\r\n" ) );
        }
    }

    /* Cleanup PKCS#11. */
    if( NULL != pxFunctionList )
    {
        ( void ) pxFunctionList->C_CloseSession( xSession );
        ( void ) pxFunctionList->C_Finalize( NULL );
    }

    TEST_ASSERT_EQUAL_INT32( 0, xResult );
}

TEST( Full_PKCS11, C_PKCSFindObjectsInitInvalidParams )
{
    CK_RV xResult = 0;
    CK_OBJECT_CLASS xPublicKeyClass = CKO_PUBLIC_KEY;
    CK_FUNCTION_LIST_PTR pxFunctionList = NULL;
    CK_SLOT_ID xSlotId = 0;
    CK_SESSION_HANDLE xSession = 0;
    CK_OBJECT_HANDLE xObject = 0;
    CK_BBOOL xObjCreated = CK_FALSE;

    /* It doesn't matter what key type is passed. The key type will be automatically
     * identified. */
    CK_KEY_TYPE xKeyType = CKK_RSA;

    /* Public key configuration template. */
    CK_ATTRIBUTE xPublicKeyTemplate[] =
    {
        { CKA_CLASS,    &xPublicKeyClass, sizeof( xPublicKeyClass ) },
        { CKA_KEY_TYPE, &xKeyType,        sizeof( xKeyType )        },
        { CKA_VALUE,
          ( CK_VOID_PTR ) pcValidRSAPublicKey,
          ( CK_ULONG ) strlen( pcValidRSAPublicKey ) + 1 }
    };

    /* Reprovision with test RSA certificate and private key. */
    prvReprovision( pcValidRSACertificate, pcValidRSAPrivateKey, CKK_RSA );

    /* Initialize the module and start a private session. */
    xResult = prvInitializeAndStartSession(
        &pxFunctionList,
        &xSlotId,
        &xSession );

    if( 0 != xResult )
    {
        configPRINTF( ( "Could not start session.\r\n" ) );
    }

    /* Create an object using the public key. */
    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_CreateObject(
            xSession,
            xPublicKeyTemplate,
            sizeof( xPublicKeyTemplate ) / sizeof( CK_ATTRIBUTE ),
            &xObject
            );

        if( 0 != xResult )
        {
            configPRINTF( ( "Could not create object.\r\n" ) );
        }
        else
        {
            xObjCreated = CK_TRUE;
        }
    }

    /* Get the (first) certificate handle. */
    if( 0 == xResult )
    {
        if( TEST_PROTECT() )
        {
            xResult = pxFunctionList->C_FindObjectsInit(
                xSession, NULL, 1 );
            TEST_ASSERT_EQUAL_INT32_MESSAGE( xResult, CKR_ARGUMENTS_BAD, "Unexpected status from C_FindObjectsInit" );
        }

        xResult = pxFunctionList->C_FindObjectsFinal( xSession );
    }

    /* Free the public key. */
    if( xObjCreated == CK_TRUE )
    {
        xResult = pxFunctionList->C_DestroyObject(
            xSession,
            xObject );
        xObject = 0;

        if( 0 != xResult )
        {
            configPRINTF( ( "Could not destroy object.\r\n" ) );
        }
    }

    /* Cleanup PKCS#11. */
    if( NULL != pxFunctionList )
    {
        ( void ) pxFunctionList->C_CloseSession( xSession );
        ( void ) pxFunctionList->C_Finalize( NULL );
    }

    TEST_ASSERT_EQUAL_INT32( 0, xResult );
}

/*-----------------------------------------------------------*/
TEST( Full_PKCS11, C_PKCSGetAttributeValueInvalidParams )
{
    CK_RV xResult = 0;
    CK_FUNCTION_LIST_PTR pxFunctionList = NULL;
    CK_SLOT_ID xSlotId = 0;
    CK_SESSION_HANDLE xSession = 0;
    CK_ULONG ulCount = 0;
    CK_ATTRIBUTE xTemplate = { 0 };
    CK_OBJECT_CLASS xObjClass = 0;
    CK_OBJECT_HANDLE xPrivateKey = 0;
    CK_ULONG ulKeyType = 0;
    CK_BYTE pucMessage[ cryptoSHA256_DIGEST_BYTES ] = { 0 };
    CK_BYTE pucHash[ cryptoSHA256_DIGEST_BYTES ] = { 0 };

    prvReprovision( pcValidRSACertificate, pcValidRSAPrivateKey, CKK_RSA );

    /* Hash the message (the null input). */
   #ifdef MBEDTLS
    ( void ) mbedtls_sha256_ret( pucMessage, 0, pucHash, 0 );
#else
{
    uint32_t hashLen = cryptoSHA256_DIGEST_BYTES;
    qcom_crypto_sha256(pucMessage,cryptoSHA256_DIGEST_BYTES,pucHash,&hashLen);
}
#endif

    /* Initialize the module and start a private session. */
    xResult = prvInitializeAndStartSession(
        &pxFunctionList,
        &xSlotId,
        &xSession );

    /* Get the (first) private key handle. */
    if( 0 == xResult )
    {
        xTemplate.type = CKA_CLASS;
        xTemplate.ulValueLen = sizeof( CKA_CLASS );
        xTemplate.pValue = &xObjClass;
        xObjClass = CKO_PRIVATE_KEY;
        xResult = pxFunctionList->C_FindObjectsInit(
            xSession, &xTemplate, 1 );
    }

    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_FindObjects(
            xSession,
            &xPrivateKey,
            1,
            &ulCount );
    }

    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_FindObjectsFinal( xSession );
    }

    /* Query the key type. */
    if( 0 == xResult )
    {
        if( TEST_PROTECT() )
        {
            xTemplate.type = CKA_KEY_TYPE;
            xTemplate.ulValueLen = sizeof( ulKeyType );
            xTemplate.pValue = &ulKeyType;

            xResult = pxFunctionList->C_GetAttributeValue(
                xSession,
                xPrivateKey,
                NULL,
                1 );
            TEST_ASSERT_EQUAL_INT32_MESSAGE( xResult, CKR_ARGUMENTS_BAD, "Unexpected status from C_GetAttribute" );

            xResult = 0;
        }
    }

    /* Clean-up. */
    if( NULL != pxFunctionList )
    {
        ( void ) pxFunctionList->C_CloseSession( xSession );
        ( void ) pxFunctionList->C_Finalize( NULL );
    }

    TEST_ASSERT_EQUAL_INT32( 0, xResult );
}

TEST( Full_PKCS11, C_PKCSGenerateRandomTestHappyTest )
{
    CK_SESSION_HANDLE xSession = 0;
    CK_RV xResult = 0;
    CK_FUNCTION_LIST_PTR pxFunctionList = NULL;
    CK_SLOT_ID xSlotId = 0;
    CK_BYTE xBuf[ 1 ];

    /* Reprovision with test RSA certificate and private key. */
    prvReprovision( pcValidRSACertificate, pcValidRSAPrivateKey, CKK_RSA );

    /* Initialize the module and start a private session. */
    xResult = prvInitializeAndStartSession(
        &pxFunctionList,
        &xSlotId,
        &xSession );

    if( 0 != xResult )
    {
        configPRINTF( ( "Could not start session.\r\n" ) );
    }

    if( 0 == xResult )
    {
        xResult = C_GenerateRandom( xSession, xBuf, 1 );
    }
    else
    {
        configPRINTF( ( "Could generate random numbers.\r\n" ) );
    }

    /* Cleanup PKCS#11. */
    if( NULL != pxFunctionList )
    {
        ( void ) pxFunctionList->C_CloseSession( xSession );
        ( void ) pxFunctionList->C_Finalize( NULL );
    }

    TEST_ASSERT_EQUAL_INT32( 0, xResult );
}

TEST( Full_PKCS11, C_PKCSGenerateRandomInvalidParameters )
{
    CK_SESSION_HANDLE xSession = 0;
    CK_RV xResult = 0;
    CK_FUNCTION_LIST_PTR pxFunctionList = NULL;
    CK_SLOT_ID xSlotId = 0;
    CK_BYTE xBuf[ 1 ];

    /* Reprovision with test RSA certificate and private key. */
    prvReprovision( pcValidRSACertificate, pcValidRSAPrivateKey, CKK_RSA );

    /* Initialize the module and start a private session. */
    xResult = prvInitializeAndStartSession(
        &pxFunctionList,
        &xSlotId,
        &xSession );

    if( 0 != xResult )
    {
        configPRINTF( ( "Could not start session.\r\n" ) );
    }

    if( 0 == xResult )
    {
        if( TEST_PROTECT() )
        {
            xResult = C_GenerateRandom( xSession, NULL, 1 );
            TEST_ASSERT_EQUAL_INT32_MESSAGE( xResult, CKR_ARGUMENTS_BAD, "Unexpected status from C_GenerateRandom" );

            xResult = C_GenerateRandom( xSession, xBuf, 0 );
            TEST_ASSERT_EQUAL_INT32_MESSAGE( xResult, CKR_ARGUMENTS_BAD, "Unexpected status from C_GenerateRandom" );
        }

        xResult = 0;
    }
    else
    {
        configPRINTF( ( "Could generate random numbers.\r\n" ) );
    }

    /* Cleanup PKCS#11. */
    if( NULL != pxFunctionList )
    {
        ( void ) pxFunctionList->C_CloseSession( xSession );
        ( void ) pxFunctionList->C_Finalize( NULL );
    }

    TEST_ASSERT_EQUAL_INT32( 0, xResult );
}

TEST( Full_PKCS11, C_PKCSCreateObjectInvalidParameters )
{
    CK_RV xResult = 0;
    CK_OBJECT_CLASS xPublicKeyClass = CKO_PUBLIC_KEY;
    CK_FUNCTION_LIST_PTR pxFunctionList = NULL;
    CK_SLOT_ID xSlotId = 0;
    CK_SESSION_HANDLE xSession = 0;
    CK_OBJECT_HANDLE xObject = 0;

    /* It doesn't matter what key type is passed. The key type will be automatically
     * identified. */
    CK_KEY_TYPE xKeyType = CKK_RSA;

    /* Public key configuration template. */
    CK_ATTRIBUTE xPublicKeyTemplate[] =
    {
        { CKA_CLASS,    &xPublicKeyClass, sizeof( xPublicKeyClass ) },
        { CKA_KEY_TYPE, &xKeyType,        sizeof( xKeyType )        },
        { CKA_VALUE,
          ( CK_VOID_PTR ) pcValidRSAPublicKey,
          ( CK_ULONG ) strlen( pcValidRSAPublicKey ) + 1 }
    };

    /* Reprovision with test RSA certificate and private key. */
    prvReprovision( pcValidRSACertificate, pcValidRSAPrivateKey, CKK_RSA );

    /* Initialize the module and start a private session. */
    xResult = prvInitializeAndStartSession(
        &pxFunctionList,
        &xSlotId,
        &xSession );

    if( 0 != xResult )
    {
        configPRINTF( ( "Could not start session.\r\n" ) );
    }

    /* Create an object using the public key. */
    if( 0 == xResult )
    {
        if( TEST_PROTECT() )
        {
            xResult = pxFunctionList->C_CreateObject(
                xSession,
                NULL,
                sizeof( xPublicKeyTemplate ) / sizeof( CK_ATTRIBUTE ),
                &xObject );
            TEST_ASSERT_EQUAL_INT32_MESSAGE( xResult, CKR_ARGUMENTS_BAD, "Unexpected status from object creation" );


            xResult = pxFunctionList->C_CreateObject(
                xSession,
                xPublicKeyTemplate,
                sizeof( xPublicKeyTemplate ) / sizeof( CK_ATTRIBUTE ),
                NULL );
            TEST_ASSERT_EQUAL_INT32_MESSAGE( xResult, CKR_ARGUMENTS_BAD, "Unexpected status from object creation" );

            xResult = pxFunctionList->C_CreateObject(
                xSession,
                xPublicKeyTemplate,
                ( CK_ULONG ) -1, /* Maximum possible length (unsigned) should be invalid. */
                &xObject );
            TEST_ASSERT_EQUAL_INT32_MESSAGE( xResult, CKR_ARGUMENTS_BAD, "Unexpected status from object creation" );

            /* Free the public key. */
            if( 0 == xResult )
            {
                xResult = pxFunctionList->C_DestroyObject(
                    xSession,
                    xObject );
                xObject = 0;

                if( 0 != xResult )
                {
                    configPRINTF( ( "Could not destroy object.\r\n" ) );
                }
            }
            else
            {
                xResult = 0;
            }
        }
    }

    /* Cleanup PKCS#11. */
    if( NULL != pxFunctionList )
    {
        ( void ) pxFunctionList->C_CloseSession( xSession );
        ( void ) pxFunctionList->C_Finalize( NULL );
    }

    TEST_ASSERT_EQUAL_INT32( 0, xResult );
}

TEST( Full_PKCS11, C_PKCSHappyTestSign )
{
    CK_RV xResult = 0;
    CK_FUNCTION_LIST_PTR pxFunctionList = NULL;
    CK_SLOT_ID xSlotId = 0;
    CK_SESSION_HANDLE xSession = 0;
    CK_ULONG ulCount = 0;
    CK_ATTRIBUTE xTemplate = { 0 };
    CK_OBJECT_CLASS xObjClass = 0;
    CK_OBJECT_HANDLE xPrivateKey = 0;
    CK_ULONG ulKeyType = 0;
    CK_MECHANISM xMech = { 0 };
    CK_BYTE pucMessage[ cryptoSHA256_DIGEST_BYTES ] = { 0 };
    CK_BYTE pucHash[ cryptoSHA256_DIGEST_BYTES ] = { 0 };
    CK_BYTE pucSignature[ 256 ] = { 0 };

    prvReprovision( pcValidRSACertificate, pcValidRSAPrivateKey, CKK_RSA );

    /* Hash the message (the null input). */
#ifdef MBEDTLS
    ( void ) mbedtls_sha256_ret( pucMessage, 0, pucHash, 0 );
#else
{
    uint32_t hashLen = cryptoSHA256_DIGEST_BYTES;
    qcom_crypto_sha256(pucMessage,cryptoSHA256_DIGEST_BYTES,pucHash,&hashLen);
}
#endif

    /* Initialize the module and start a private session. */
    xResult = prvInitializeAndStartSession(
        &pxFunctionList,
        &xSlotId,
        &xSession );

    /* Get the (first) private key handle. */
    if( 0 == xResult )
    {
        xTemplate.type = CKA_CLASS;
        xTemplate.ulValueLen = sizeof( CKA_CLASS );
        xTemplate.pValue = &xObjClass;
        xObjClass = CKO_PRIVATE_KEY;
        xResult = pxFunctionList->C_FindObjectsInit(
            xSession, &xTemplate, 1 );
    }

    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_FindObjects(
            xSession,
            &xPrivateKey,
            1,
            &ulCount );
    }

    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_FindObjectsFinal( xSession );
    }

    /* Query the key type. */
    if( 0 == xResult )
    {
        xTemplate.type = CKA_KEY_TYPE;
        xTemplate.ulValueLen = sizeof( ulKeyType );
        xTemplate.pValue = &ulKeyType;
        xResult = pxFunctionList->C_GetAttributeValue(
            xSession,
            xPrivateKey,
            &xTemplate,
            1 );
    }

    /* Sign a hash. */
    if( 0 == xResult )
    {
        xMech.mechanism = CKM_SHA256_RSA_PKCS;
        xResult = pxFunctionList->C_SignInit(
            xSession,
            &xMech,
            xPrivateKey );
    }

    if( 0 == xResult )
    {
        /* TODO - query the key size instead. */
        ulCount = sizeof( pucSignature );
        xResult = pxFunctionList->C_Sign(
            xSession,
            pucHash,
            sizeof( pucHash ),
            pucSignature,
            &ulCount );
    }

    /* Clean-up. */
    if( NULL != pxFunctionList )
    {
        ( void ) pxFunctionList->C_CloseSession( xSession );
        ( void ) pxFunctionList->C_Finalize( NULL );
    }

    TEST_ASSERT_EQUAL_INT32( 0, xResult );
}

TEST( Full_PKCS11, C_PKCSHappyTestObject )
{
    CK_RV xResult = 0;
    CK_OBJECT_CLASS xPublicKeyClass = CKO_PUBLIC_KEY;
    CK_FUNCTION_LIST_PTR pxFunctionList = NULL;
    CK_SLOT_ID xSlotId = 0;
    CK_SESSION_HANDLE xSession = 0;
    CK_OBJECT_HANDLE xObject = 0;
    CK_BBOOL xObjCreated = CK_FALSE;
    CK_ATTRIBUTE xTemplate = { 0 };
    CK_OBJECT_CLASS xObjClass = 0;
    CK_OBJECT_HANDLE xCertObj = 0;
    CK_ULONG ulCount = 0;

    /* It doesn't matter what key type is passed. The key type will be automatically
     * identified. */
    CK_KEY_TYPE xKeyType = CKK_RSA;

    /* Public key configuration template. */
    CK_ATTRIBUTE xPublicKeyTemplate[] =
    {
        { CKA_CLASS,    &xPublicKeyClass, sizeof( xPublicKeyClass ) },
        { CKA_KEY_TYPE, &xKeyType,        sizeof( xKeyType )        },
        { CKA_VALUE,
          ( CK_VOID_PTR ) pcValidRSAPublicKey,
          ( CK_ULONG ) strlen( pcValidRSAPublicKey ) + 1 }
    };

    /* Reprovision with test RSA certificate and private key. */
    prvReprovision( pcValidRSACertificate, pcValidRSAPrivateKey, CKK_RSA );

    /* Initialize the module and start a private session. */
    xResult = prvInitializeAndStartSession(
        &pxFunctionList,
        &xSlotId,
        &xSession );

    if( 0 != xResult )
    {
        configPRINTF( ( "Could not start session.\r\n" ) );
    }

    /* Create an object using the public key. */
    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_CreateObject(
            xSession,
            xPublicKeyTemplate,
            sizeof( xPublicKeyTemplate ) / sizeof( CK_ATTRIBUTE ),
            &xObject
            );

        if( 0 != xResult )
        {
            configPRINTF( ( "Could not create object.\r\n" ) );
        }
        else
        {
            xObjCreated = CK_TRUE;
        }
    }

    /* Get the (first) certificate handle. */
    if( 0 == xResult )
    {
        xTemplate.type = CKA_CLASS;
        xTemplate.ulValueLen = sizeof( CKA_CLASS );
        xTemplate.pValue = &xObjClass;
        xObjClass = CKO_CERTIFICATE;
        xResult = pxFunctionList->C_FindObjectsInit(
            xSession, &xTemplate, 1 );
    }

    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_FindObjects(
            xSession,
            &xCertObj,
            1,
            &ulCount );
    }

    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_FindObjectsFinal( xSession );
    }

    /* Free the public key. */
    if( xObjCreated == CK_TRUE )
    {
        xResult = pxFunctionList->C_DestroyObject(
            xSession,
            xObject );
        xObject = 0;

        if( 0 != xResult )
        {
            configPRINTF( ( "Could not destroy object.\r\n" ) );
        }
    }

    /* Cleanup PKCS#11. */
    if( NULL != pxFunctionList )
    {
        ( void ) pxFunctionList->C_CloseSession( xSession );
        ( void ) pxFunctionList->C_Finalize( NULL );
    }

    TEST_ASSERT_EQUAL_INT32( 0, xResult );
}

TEST( Full_PKCS11, C_PKCSHappyTestVerify )
{
    CK_RV xResult = 0;
    CK_FUNCTION_LIST_PTR pxFunctionList = NULL;
    CK_SLOT_ID xSlotId = 0;
    CK_SESSION_HANDLE xSession = 0;
    CK_MECHANISM xMech = { 0 };
    CK_OBJECT_HANDLE xPublicKey = 0;


    /* Reprovision with test RSA certificate and private key. */
    prvReprovision( pcValidRSACertificate, pcValidRSAPrivateKey, CKK_RSA );

    /* Initialize the module and start a private session. */
    xResult = prvInitializeAndStartSession(
        &pxFunctionList,
        &xSlotId,
        &xSession );

    if( 0 != xResult )
    {
        configPRINTF( ( "Could not start session.\r\n" ) );
    }

    if( 0 == xResult )
    {
        xResult = prvImportPublicKey( xSession,
                                      pxFunctionList,
                                      &xPublicKey,
                                      pcValidRSAPublicKey );

        if( 0 != xResult )
        {
            configPRINTF( ( "Failed to import public key.\r\n" ) );
        }
    }

    /* Verify the signature using the same key handle. */
    if( 0 == xResult )
    {
        xMech.mechanism = CKM_SHA256_RSA_PKCS;
        xResult = pxFunctionList->C_VerifyInit(
            xSession,
            &xMech,
            xPublicKey );

        if( 0 != xResult )
        {
            configPRINTF( ( "Failed to initialize signature verification.\r\n" ) );
        }
    }

    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_Verify(
            xSession,
            ( CK_BYTE_PTR ) pcEmptyStringHash,
            ( CK_ULONG ) sizeof( pcEmptyStringHash ),
            ( CK_BYTE_PTR ) pcSignedData,
            ( CK_ULONG ) sizeof( pcSignedData ) );
    }

    /* Cleanup PKCS#11. */
    if( NULL != pxFunctionList )
    {
        ( void ) pxFunctionList->C_CloseSession( xSession );
        ( void ) pxFunctionList->C_Finalize( NULL );
    }

    TEST_ASSERT_EQUAL_INT32( 0, xResult );
}

/*-----------------------------------------------------------*/

TEST( Full_PKCS11, GetFunctionListInvalidParams )
{
    CK_FUNCTION_LIST_PTR pxFunctionList = NULL;

    TEST_ASSERT_EQUAL( CKR_ARGUMENTS_BAD, C_GetFunctionList( NULL ) );

    TEST_ASSERT_EQUAL( CKR_OK, C_GetFunctionList( &pxFunctionList ) );

    /* Ensure that pxFunctionList was changed by C_GetFunctionList. */
    TEST_ASSERT_NOT_EQUAL( NULL, pxFunctionList );
}

/*-----------------------------------------------------------*/

TEST( Full_PKCS11, InitializeFinalizeInvalidParams )
{
    CK_FUNCTION_LIST_PTR pxFunctionList = NULL;

    TEST_ASSERT_EQUAL( CKR_OK, C_GetFunctionList( &pxFunctionList ) );

    /* C_Finalize should fail if pReserved isn't NULL. It shouldn't matter that
     * C_Finalize is called before C_Initialize because the failing C_Finalize call
     * should do nothing. */
    TEST_ASSERT_EQUAL( CKR_ARGUMENTS_BAD,
                       pxFunctionList->C_Finalize( ( CK_VOID_PTR ) 0x1234 ) );

    /* Currently, C_Initialize doesn't support use of pInitArgs. Pass NULL. */
    if( CKR_OK == pxFunctionList->C_Initialize( NULL ) )
    {
        TEST_ASSERT_EQUAL( CKR_OK, pxFunctionList->C_Finalize( NULL ) );
    }
    else
    {
        TEST_FAIL();
    }
}

/*-----------------------------------------------------------*/

TEST( Full_PKCS11, GetSlotListInvalidParams )
{
    CK_FUNCTION_LIST_PTR pxFunctionList = NULL;
    CK_SLOT_ID xSlotId = 0;
    CK_ULONG ulSlotCount = 0;

    TEST_ASSERT_EQUAL( CKR_OK, C_GetFunctionList( &pxFunctionList ) );

    if( CKR_OK == pxFunctionList->C_Initialize( NULL ) )
    {
        if( TEST_PROTECT() )
        {
            /* Passing NULL as pulCount isn't valid. */
            TEST_ASSERT_EQUAL( CKR_ARGUMENTS_BAD,
                               pxFunctionList->C_GetSlotList( CK_FALSE, NULL, NULL ) );

            /* Passing 0 for slot count and attempting to get slot list isn't valid. */
            ulSlotCount = 0;
            TEST_ASSERT_EQUAL( CKR_BUFFER_TOO_SMALL,
                               pxFunctionList->C_GetSlotList( CK_FALSE, &xSlotId, &ulSlotCount ) );

            /* This should get the number of slots. Check that ulSlotCount changed. */
            TEST_ASSERT_EQUAL( CKR_OK,
                               pxFunctionList->C_GetSlotList( CK_FALSE, NULL, &ulSlotCount ) );
            TEST_ASSERT_NOT_EQUAL( 0, ulSlotCount );

            /* Get slot list, all inputs valid. */
            TEST_ASSERT_EQUAL( CKR_OK,
                               pxFunctionList->C_GetSlotList( CK_FALSE, &xSlotId, &ulSlotCount ) );
            TEST_ASSERT_NOT_EQUAL( 0, xSlotId );
        }

        pxFunctionList->C_Finalize( NULL );
    }
    else
    {
        TEST_FAIL();
    }
}

/*-----------------------------------------------------------*/

TEST( Full_PKCS11, OpenCloseSessionInvalidParams )
{
    CK_FUNCTION_LIST_PTR pxFunctionList = NULL;
    CK_SLOT_ID xSlotId = 0;
    CK_ULONG ulSlotCount = 0;
    CK_SESSION_HANDLE xSession = 0;

    TEST_ASSERT_EQUAL( CKR_OK, C_GetFunctionList( &pxFunctionList ) );

    if( CKR_OK == pxFunctionList->C_Initialize( NULL ) )
    {
        if( TEST_PROTECT() )
        {
            /* Get slot list. */
            TEST_ASSERT_EQUAL( CKR_OK,
                               pxFunctionList->C_GetSlotList( CK_TRUE, NULL, &ulSlotCount ) );
            TEST_ASSERT_EQUAL( CKR_OK,
                               pxFunctionList->C_GetSlotList( CK_TRUE, &xSlotId, &ulSlotCount ) );

            /* Test C_OpenSession with bad pxSession argument. */
            TEST_ASSERT_EQUAL( CKR_ARGUMENTS_BAD,
                               pxFunctionList->C_OpenSession( xSlotId, 0, NULL, NULL, NULL ) );

            /* Test C_OpenSession with valid arguments. */
            TEST_ASSERT_EQUAL( CKR_OK,
                               pxFunctionList->C_OpenSession( xSlotId, 0, NULL, NULL, &xSession ) );
            TEST_ASSERT_NOT_EQUAL( 0, xSession );

            /* C_CloseSession with invalid argument. */
            TEST_ASSERT_EQUAL( CKR_SESSION_HANDLE_INVALID,
                               pxFunctionList->C_CloseSession( ( CK_SESSION_HANDLE ) NULL ) );

            /* C_CloseSession with valid argument. */
            if( CKR_OK == pxFunctionList->C_CloseSession( xSession ) )
            {
                xSession = 0;
            }
            else
            {
                TEST_FAIL();
            }
        }

        /* If a session is left open due to test failure, close it. */
        if( 0 != xSession )
        {
            pxFunctionList->C_CloseSession( xSession );
        }

        pxFunctionList->C_Finalize( NULL );
    }
    else
    {
        TEST_FAIL();
    }
}

/*-----------------------------------------------------------*/

TEST( Full_PKCS11, TestRSAParse )
{
    if( TEST_PROTECT() )
    {
        /* Ensure that valid cert and keys are successfully imported. */
        if( prvImportCertificateAndKeys( pcValidRSACertificate,
                                         pcValidRSAPrivateKey,
                                         pcValidRSAPublicKey,
                                         CKK_RSA ) != 0 )
        {
            TEST_FAIL();
        }

        /* Ensure that an invalid cert with valid keys is rejected. */
        if( prvImportCertificateAndKeys( pcInvalidRSACertificate,
                                         pcValidRSAPrivateKey,
                                         pcValidRSAPublicKey,
                                         CKK_RSA ) == 0 )
        {
            TEST_FAIL();
        }

        /* Ensure that a valid cert with invalid private key is rejected. */
        if( prvImportCertificateAndKeys( pcValidRSACertificate,
                                         pcInvalidRSAPrivateKey,
                                         pcValidRSAPublicKey,
                                         CKK_RSA ) == 0 )
        {
            TEST_FAIL();
        }

        /* Ensure that a valid cert with invalid public key is rejected. */
        if( prvImportCertificateAndKeys( pcValidRSACertificate,
                                         pcValidRSAPrivateKey,
                                         pcInvalidRSAPublicKey,
                                         CKK_RSA ) == 0 )
        {
            TEST_FAIL();
        }
    }
}

/*-----------------------------------------------------------*/

TEST( Full_PKCS11, TestECDSAParse )
{
    if( TEST_PROTECT() )
    {
        /* Ensure that valid cert and keys are successfully parsed. */
        if( prvImportCertificateAndKeys( pcValidECDSACertificate,
                                         pcValidECDSAPrivateKey,
                                         pcValidECDSAPublicKey,
                                         CKK_EC ) != 0 )
        {
            TEST_FAIL();
        }

        /* Ensure that an invalid cert with valid keys is rejected. */
        if( prvImportCertificateAndKeys( pcInvalidECDSACertificate,
                                         pcValidECDSAPrivateKey,
                                         pcValidECDSAPublicKey,
                                         CKK_EC ) == 0 )
        {
            TEST_FAIL();
        }

        /* Ensure that a valid cert with invalid private key is rejected. */
        if( prvImportCertificateAndKeys( pcValidECDSACertificate,
                                         pcInvalidECDSAPrivateKey,
                                         pcValidECDSAPublicKey,
                                         CKK_EC ) == 0 )
        {
            TEST_FAIL();
        }

        /* Ensure that a valid cert with invalid public key is rejected. */
        if( prvImportCertificateAndKeys( pcValidECDSACertificate,
                                         pcValidECDSAPrivateKey,
                                         pcInvalidECDSAPublicKey,
                                         CKK_EC ) == 0 )
        {
            TEST_FAIL();
        }
    }
}

/*-----------------------------------------------------------*/

TEST( Full_PKCS11, TestRSAExport )
{
    TEST_ASSERT_EQUAL_INT32( prvExportCertificateAndKeys( pcValidRSACertificate,
                                                          pcValidRSAPrivateKey,
                                                          pcValidRSAPublicKey,
                                                          CKK_RSA ),
                             0 );
}

/*-----------------------------------------------------------*/

TEST( Full_PKCS11, TestECDSAExport )
{
    TEST_ASSERT_EQUAL_INT32( prvExportCertificateAndKeys( pcValidECDSACertificate,
                                                          pcValidECDSAPrivateKey,
                                                          pcValidECDSAPublicKey,
                                                          CKK_EC ),
                             0 );
}

/*-----------------------------------------------------------*/

TEST( Full_PKCS11, SignVerifyRoundTripRSANoPubKey )
{
    /* Reprovision with test RSA certificate and private key. */
    prvReprovision( pcValidRSACertificate, pcValidRSAPrivateKey, CKK_RSA );

    TEST_ASSERT_EQUAL_INT32( prvSignVerifyRoundTrip( CKM_SHA256_RSA_PKCS,
                                                     NULL ),
                             0 );
}

/*-----------------------------------------------------------*/

TEST( Full_PKCS11, SignVerifyRoundTripWithCorrectRSAPublicKey )
{
    /* Reprovision with test RSA certificate and private key. */
    prvReprovision( pcValidRSACertificate, pcValidRSAPrivateKey, CKK_RSA );

    TEST_ASSERT_EQUAL_INT32( prvSignVerifyRoundTrip( CKM_SHA256_RSA_PKCS,
                                                     pcValidRSAPublicKey ),
                             0 );
}

/*-----------------------------------------------------------*/

TEST( Full_PKCS11, SignVerifyRoundTripWithWrongRSAPublicKey )
{
    /* Reprovision with test RSA certificate and private key. */
    prvReprovision( pcValidRSACertificate, pcValidRSAPrivateKey, CKK_RSA );

    /* Pass a public key that isn't paired with the default private key. Verification
     * should fail. */
    TEST_ASSERT_NOT_EQUAL( prvSignVerifyRoundTrip( CKM_SHA256_RSA_PKCS,
                                                   pcWrongRSAPublicKey ),
                           0 );
}

/*-----------------------------------------------------------*/

TEST( Full_PKCS11, SignVerifyRoundTripECNoPubKey )
{
    /* Reprovision with test ECDSA certificate and private key. */
    prvReprovision( pcValidECDSACertificate, pcValidECDSAPrivateKey, CKK_EC );

    TEST_ASSERT_EQUAL_INT32( prvSignVerifyRoundTrip( CKM_ECDSA,
                                                     NULL ),
                             0 );
}

/*-----------------------------------------------------------*/

TEST( Full_PKCS11, SignVerifyRoundTripWithCorrectECPublicKey )
{
    /* Reprovision with test RSA certificate and private key. */
    prvReprovision( pcValidECDSACertificate, pcValidECDSAPrivateKey, CKK_EC );

    TEST_ASSERT_EQUAL_INT32( prvSignVerifyRoundTrip( CKM_ECDSA,
                                                     pcValidECDSAPublicKey ),
                             0 );
}

/*-----------------------------------------------------------*/

TEST( Full_PKCS11, SignVerifyRoundTripWithWrongECPublicKey )
{
    /* Reprovision with test ECDSA certificate and private key. */
    prvReprovision( pcValidECDSACertificate, pcValidECDSAPrivateKey, CKK_EC );

    TEST_ASSERT_NOT_EQUAL( prvSignVerifyRoundTrip( CKM_ECDSA,
                                                   pcWrongECDSAPublicKey ),
                           0 );
}

/*-----------------------------------------------------------*/

TEST( Full_PKCS11, SignVerifyCryptoApiInteropRSA )
{
    CK_RV xResult = 0;
    CK_FUNCTION_LIST_PTR pxFunctionList = NULL;
    CK_SLOT_ID xSlotId = 0;
    CK_ULONG ulCount = 0;
    CK_SESSION_HANDLE xSession = 0;
    CK_ATTRIBUTE xTemplate = { 0 };
    CK_OBJECT_CLASS xObjClass = 0;
    CK_OBJECT_HANDLE xCertObj = 0;
    CK_MECHANISM xMech = { 0 };
    CK_OBJECT_HANDLE xPublicKey = 0;

    /* Reprovision with test RSA certificate and private key. */
    prvReprovision( pcValidRSACertificate, pcValidRSAPrivateKey, CKK_RSA );

    /* Initialize the module and start a private session. */
    xResult = prvInitializeAndStartSession(
        &pxFunctionList,
        &xSlotId,
        &xSession );

    /* Get the (first) certificate handle. */
    if( 0 == xResult )
    {
        xTemplate.type = CKA_CLASS;
        xTemplate.ulValueLen = sizeof( CKA_CLASS );
        xTemplate.pValue = &xObjClass;
        xObjClass = CKO_CERTIFICATE;
        xResult = pxFunctionList->C_FindObjectsInit(
            xSession, &xTemplate, 1 );
    }

    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_FindObjects(
            xSession,
            &xCertObj,
            1,
            &ulCount );
    }

    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_FindObjectsFinal( xSession );
    }

    /* Create an object using the public key. */
    if( 0 == xResult )
    {
        xResult = prvImportPublicKey( xSession,
                                      pxFunctionList,
                                      &xPublicKey,
                                      pcValidRSAPublicKey );
    }

    /* Verify the signature using the same key handle. */
    if( 0 == xResult )
    {
        xMech.mechanism = CKM_SHA256_RSA_PKCS;
        xResult = pxFunctionList->C_VerifyInit(
            xSession,
            &xMech,
            xPublicKey );
    }

    /* Attempt to verify a valid signature. */
    if( 0 == xResult )
    {
        xResult = pxFunctionList->C_Verify(
            xSession,
            ( CK_BYTE_PTR ) pcEmptyStringHash,
            ( CK_ULONG ) sizeof( pcEmptyStringHash ),
            ( CK_BYTE_PTR ) pcSignedData,
            ( CK_ULONG ) sizeof( pcSignedData ) );
    }

    /* Create a malformed signature by dropping a byte. Attempt to verify it.
     * Verification should fail. */
    if( 0 == xResult )
    {
        if( 0 == pxFunctionList->C_Verify(
                xSession,
                ( CK_BYTE_PTR ) pcEmptyStringHash,
                ( CK_ULONG ) sizeof( pcEmptyStringHash ),
                ( CK_BYTE_PTR ) pcSignedData,
                ( CK_ULONG ) sizeof( pcSignedData ) - 1 ) )
        {
            xResult = CKR_FUNCTION_FAILED;
        }
        else
        {
            xResult = CKR_OK;
        }
    }

    /* Clean-up. */
    if( 0 != xPublicKey )
    {
        xResult = pxFunctionList->C_DestroyObject(
            xSession,
            xPublicKey );
        xPublicKey = 0;
    }

    if( ( NULL != pxFunctionList ) &&
        ( NULL != pxFunctionList->C_CloseSession ) )
    {
        pxFunctionList->C_CloseSession( xSession );
        pxFunctionList->C_Finalize( NULL );
    }

    TEST_ASSERT_EQUAL_INT32( xResult, 0 );
}

/*-----------------------------------------------------------*/

TEST( Full_PKCS11, SignVerifyRoundTrip_MultitaskLoop )
{
    SignVerifyTaskParams_t xTaskParams[ pkcs11testSIGN_VERIFY_TASK_COUNT ];
    BaseType_t i;

    /* Initialize all of the xTestResult values to something other than 0,
     * as 0 means success. */
    memset( xTaskParams,
            0xFF,
            sizeof( SignVerifyTaskParams_t ) * pkcs11testSIGN_VERIFY_TASK_COUNT );

    /* Create the event group used to synchronize tasks. */
    xSyncEventGroup = xEventGroupCreate();

    if( xSyncEventGroup != NULL )
    {
        /* Create the sign verify loop tasks. */
        for( i = 0; i < pkcs11testSIGN_VERIFY_TASK_COUNT; i++ )
        {
            xTaskParams[ i ].xTaskNumber = i;

            xTaskCreate( prvSignVerifyTask,                     /* Task code. */
                         "SignVerifyTask",                      /* All tasks have same name, but are distinguished by task number. */
                         pkcs11testSIGN_VERIFY_TASK_STACK_SIZE, /* Task stack size. */
                         &( xTaskParams[ i ] ),                 /* Where the task writes its result. */
                         pkcs11testSIGN_VERIFY_TASK_PRIORITY,   /* Task priority. */
                         NULL );                                /* Task handle (not used). */
        }

        /* Wait for all tasks to finish. */
        if( xEventGroupWaitBits( xSyncEventGroup,
                                 pkcs11testALL_BITS,
                                 pdFALSE,
                                 pdTRUE,
                                 pkcs11testEVENT_GROUP_TIMEOUT_MS ) != pkcs11testALL_BITS )
        {
            configPRINTF( ( "Timed out waiting for SignVerify tasks to finish.\r\n" ) );
        }

        vEventGroupDelete( xSyncEventGroup );
    }

    /* Check the tasks' results. */
    if( TEST_PROTECT() )
    {
        for( i = 0; i < pkcs11testSIGN_VERIFY_TASK_COUNT; i++ )
        {
            if( xTaskParams[ i ].xTestResult != 0 )
            {
                configPRINTF( ( "SignVerify task %d returned failure.\r\n",
                                xTaskParams[ i ].xTaskNumber ) );
                TEST_FAIL();
            }
        }
    }
}

/*-----------------------------------------------------------*/
