/*
 * PEM-encoded client certificate
 *
 * Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----"
 * "...base64 data..."
 * "-----END CERTIFICATE-----";
 */
/*from AWS IOT:
arn:aws:iot:ap-southeast-1:233763972509:cert/88ea8b37b88bceaf298c899b48e4a42899e7e2859df977181ddd5f2f7e977a42
*/
static const char clientcredentialCLIENT_CERTIFICATE_PEM[] = 
"-----BEGIN CERTIFICATE-----\n"
"MIIDWjCCAkKgAwIBAgIVALTa0qLyaVsvOew7Q3AbfUS1w4F8MA0GCSqGSIb3DQEB\n"
"CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n"
"IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0xODA3MjAwMzU5\n"
"MjFaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\n"
"dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCuaUaYhuh8+voDIemr\n"
"5GSI60l33ZzPgqV2XVl8TYt+X1HB+PTF+51vTUrVNPon5R+OZzkoLEQomHpm0C2v\n"
"BLp1rDe+jq6jeWWHNx/lVxWLUrzW3oIg86CNdzhJzjlyAXJPppdV43sWkpfd2kEe\n"
"5D7zq8r/SxPysBtVvvACj3nK2cx+/v1SnO86QGvDavGIseHo86iOp1MX4f7vZFG+\n"
"eY8edVHVW824BhoEdDzCbRTeDfsRAiNYblXoqTU1LoZoWZ2CC4lABzRKs0Rvrv67\n"
"gZFnLjkblw6L/PbnWS38Owsbc3vhsnrP7JfvgpJNJKm1r8klI3CqIAz+dcNJ2EPI\n"
"F3nDAgMBAAGjYDBeMB8GA1UdIwQYMBaAFBGQBpse/4lyYiNiKbaAjJl5ObTVMB0G\n"
"A1UdDgQWBBTLou4ypc5dd5g8T6G2GbVKWuLOPzAMBgNVHRMBAf8EAjAAMA4GA1Ud\n"
"DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAElTvWZg7k8Wi614qSKo6Qs44\n"
"AOreMQqUIfcxzSmA4g2xAKqKutOzhYc+Itu/a6Ed8Sniu+8QYK34c8MyfpdLwxU1\n"
"0dl9N3XSahb+8psFMdSDRTaKq6tcmnU8PuykyHNOZ/fo5mtTH3hXyzwbGF8BapGn\n"
"xg8dWlTxvsT5f6tn2SOZFulyp/L3/QTgjnQkRl2j0zN7Qr/6qySeDFFOK9SSSH47\n"
"Bxi9Qwe1Jcf01F0Ku8/x00Gywah3U4b0zLpya/wThq3kqKYv6aXujoi/9qZkqJ/+\n"
"xiS+aGYgxvCDHW3UvmQNw6WPHpTTx90MDzRe3N0eF6VJm1ngtBAbC4V9cnJi/A==\n"
"-----END CERTIFICATE-----";

/*
 * PEM-encoded issuer certificate for AWS IoT Just In Time Registration (JITR).
 * This is required if you're using JITR, since the issuer (Certificate
 * Authority) of the client certificate is used by the server for routing the
 * device's initial request. (The device client certificate must always be
 * sent as well.) For more information about JITR, see:
 *  https://docs.aws.amazon.com/iot/latest/developerguide/jit-provisioning.html,
 *  https://aws.amazon.com/blogs/iot/just-in-time-registration-of-device-certificates-on-aws-iot/.
 *
 * If you're not using JITR, set the below pointer to NULL.
 *
 * Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----"
 * "...base64 data..."
 * "-----END CERTIFICATE-----";
 */
static const char * clientcredentialJITR_DEVICE_CERTIFICATE_AUTHORITY_PEM = NULL;

/*
 * PEM-encoded client private key.
 *
 * Must include the PEM header and footer:
 * "-----BEGIN RSA PRIVATE KEY-----"
 * "...base64 data..."
 * "-----END RSA PRIVATE KEY-----";
 */

static const char clientcredentialCLIENT_PRIVATE_KEY_PEM[] = 
"-----BEGIN RSA PRIVATE KEY-----\n"
"MIIEowIBAAKCAQEArmlGmIbofPr6AyHpq+RkiOtJd92cz4Kldl1ZfE2Lfl9Rwfj0\n"
"xfudb01K1TT6J+Ufjmc5KCxEKJh6ZtAtrwS6daw3vo6uo3llhzcf5VcVi1K81t6C\n"
"IPOgjXc4Sc45cgFyT6aXVeN7FpKX3dpBHuQ+86vK/0sT8rAbVb7wAo95ytnMfv79\n"
"UpzvOkBrw2rxiLHh6POojqdTF+H+72RRvnmPHnVR1VvNuAYaBHQ8wm0U3g37EQIj\n"
"WG5V6Kk1NS6GaFmdgguJQAc0SrNEb67+u4GRZy45G5cOi/z251kt/DsLG3N74bJ6\n"
"z+yX74KSTSSpta/JJSNwqiAM/nXDSdhDyBd5wwIDAQABAoIBAFkiOk73G1fMF/uD\n"
"2FzdozeKL4jPvDUcypz8RiBNrQ2Pf0QHjGimF6ZrNORTZ8j9wqvPOxm5zbeFfYCP\n"
"wdkhLH243uBHIR8wil+ZH3bgk4UZaqLRImXevF2v4RdvClKmRJpKRCtDz4MQtgZO\n"
"ZVt5QGbdlCf2YaJ0t/ORWi2kz5SH9DyNeM+B+tu8Anym4T7jZLqW2f3yoP/rMTjg\n"
"DkG86TIHOl1bVA0Wvavuk8/9rusOBt/E7cY5AKYdUhzoegvZOv5gULzQszfOewVV\n"
"FN6dsRxWa6PzDIWUmn/c9eOU2J+dcVWILMeH5s8hqtQt4UYE5vOrjagRxSsntD0Z\n"
"OEob34kCgYEA3wUzt6raBOl3gQjOG7E/6MwqgL7nh5V0VvhHZsXUsZQv+B84UxDs\n"
"Vn3Zmxy2M81JqKVprlg8Nly2WcUNrN9bH2B1aNAePYg/2lDNcK1QX7PYF4zW1fXI\n"
"SX24+319unEFgz1mzyX5PrV340shIpH0VMREPQkkKKacEluMs3W/1u0CgYEAyDPl\n"
"wO+IzrW3fvWzbBzEDvEtARlrSEyEn5hi5lNep1tKmTNc0RLGTrTtv2ImkputoRhi\n"
"K2bDnbkLfXX2ntDueyNTprsAweyyud2TPzF6NqkulZjCKKscBt/49EQf2C3y58vD\n"
"HIVPhH7lumfDyUVcn5Ea/k+7QfW/mesJG/LUTW8CgYEApdR9ZzWwVXSwOo8siqTa\n"
"y6R8eiz5hfSYhE6q8P1rMPvqS0oTnJh507pSgybvSEd+XNtaYJwVcaqwoMGIcKHI\n"
"ZOVZiC0wPzq/l/r7N6x3liHpLWG5IXFXk2XblYzzXx3JJpQSjTdERN+0nJrxsX3r\n"
"utgRkXzpmRyB8piGX67PjeUCgYBnA51DC33/ry0+HLs39A1GCv83Q5caWpUbcdPh\n"
"5CAeSTE3Z2BpDBoSQbLb+WsToRtUezF4V6ZsL90jr2E5ExTDM8hFUI/xORQ14zdz\n"
"Gshh++fGfhXZy0Hen7yAI9Wm7O3CK+y3bjkeWhVnNyFdHV2tlYKoPOqD5Cm0z2We\n"
"hfKL7QKBgEQOMrHhVfGLgujbcWY+WHw3/LQbEsX9ShlXXDLnnjlqoTxeRnRRG56d\n"
"npwYpisjbpznkxoNBCkr+yQgQad6HL2UClW7pzOeuKshxfVTb6jk2IIkBgbZYv33\n"
"dTS8eF6GLUe4/Cr9pFXr8yKiV6+zAnA1TMXCdjnoGJ6yxIp1douN\n"
"-----END RSA PRIVATE KEY-----"; 

/* The root certificate used for the encrypted echo server.
 * This certificate is self-signed, and not in the trusted catalog. */
 /* ca.crt + ca-int.crt + server.crt for local SSL handshake*/
static const char tcptestECHO_HOST_ROOT_CA[] = 
"-----BEGIN CERTIFICATE-----\n"
"MIICvjCCAiegAwIBAgIJAJy+VrWx26F6MA0GCSqGSIb3DQEBBQUAMHgxCzAJBgNV\n"
"BAYTAklOMQswCQYDVQQIDAJUTjEQMA4GA1UEBwwHQ2hlbm5haTENMAsGA1UECgwE\n"
"UUNPTTEMMAoGA1UECwwDQ1NUMQwwCgYDVQQDDANJT0UxHzAdBgkqhkiG9w0BCQEW\n"
"EGNhLWludEBkdW1teS5jb20wHhcNMTMwOTE0MTMzMzMzWhcNMjMwOTEyMTMzMzMz\n"
"WjB4MQswCQYDVQQGEwJJTjELMAkGA1UECAwCVE4xEDAOBgNVBAcMB0NoZW5uYWkx\n"
"DTALBgNVBAoMBFFDT00xDDAKBgNVBAsMA0NTVDEMMAoGA1UEAwwDSU9FMR8wHQYJ\n"
"KoZIhvcNAQkBFhBjYS1pbnRAZHVtbXkuY29tMIGfMA0GCSqGSIb3DQEBAQUAA4GN\n"
"ADCBiQKBgQDQ+m1xxG6o2PwhhgymCTSijlqHmJUPwrO8sje5CodTnr7rGA5nwpl0\n"
"PYz1xOfLs18eJlcN9EQT9QuqwSVvY4Y3vLAlW+pXITEdaWa7vwHLyR+ECYrTblc7\n"
"M3nH09Y1SwkgnSPeCEYlefhE/hhcPc34fSUtavxxSifCPXcgU6V/xwIDAQABo1Aw\n"
"TjAdBgNVHQ4EFgQUWo/Za7VH6Bqy92lprUylP4VCXFcwHwYDVR0jBBgwFoAUWo/Z\n"
"a7VH6Bqy92lprUylP4VCXFcwDAYDVR0TBAUwAwEB/zANBgkqhkiG9w0BAQUFAAOB\n"
"gQAD+8ZvnC4GBHOIDjCsWhEE78BA8RrodTLCJTS/EXd/YGe4n/dlzdH4CS9iVSXF\n"
"Zvo1Rko4O0xr6N2CLpnt9GyZPO864c44lYrydl+IClhdESsRADQ2J9mUAXuYK5/O\n"
"Sj+VM1R4pmT5IKcENyKtZb83dxqqnJHXD76tD0/nNR+nHg==\n"
"-----END CERTIFICATE-----\n"
"-----BEGIN CERTIFICATE-----\n"
"MIICAjCCAWsCAQEwDQYJKoZIhvcNAQEFBQAweDELMAkGA1UEBhMCSU4xCzAJBgNV\n"
"BAgMAlROMRAwDgYDVQQHDAdDaGVubmFpMQ0wCwYDVQQKDARRQ09NMQwwCgYDVQQL\n"
"DANDU1QxDDAKBgNVBAMMA0lPRTEfMB0GCSqGSIb3DQEJARYQY2EtaW50QGR1bW15\n"
"LmNvbTAeFw0xMzA5MTQxMzMzNTJaFw0yMzA5MTIxMzMzNTJaMBsxGTAXBgNVBAMM\n"
"EGNhLWludEBkdW1teS5jb20wgZ8wDQYJKoZIhvcNAQEBBQADgY0AMIGJAoGBAK6v\n"
"WSouoatw6fIUqQVajeBFKqOO/l2ZhVLaZDcUE1dfOtRxY+oRRd8FxfYJR2PHIXZ5\n"
"8snbzqhEqBpQO3PynQoZ1EanQsntchl1fM4PP3hqbSSKU80FpSnGNTOKClK4ohFz\n"
"QpJTFzYGOe3XX/uM2XLkynuj2WpYmTVZV31kfM9fAgMBAAEwDQYJKoZIhvcNAQEF\n"
"BQADgYEAT1DTlQUBrBWGTe0cMUfNgHt7juAkmS148FgOZ55CCdnb3qDr9YWMrPua\n"
"Agjn6vv26iaaRe3qXcUaeyZhpYH6wtzZplr1kEhZJmD9F5Ujjk1JNyhrIqfQtOZT\n"
"YH2Vq23dnqOD7P/gc7B5ymm1z9O87SvNQmnwNy2wzR7kke28oNc=\n"
"-----END CERTIFICATE-----\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIBpTCCAQ4CAQEwDQYJKoZIhvcNAQEFBQAwGzEZMBcGA1UEAwwQY2EtaW50QGR1\n"
"bW15LmNvbTAeFw0xMzA5MTQxMzM0MDZaFw0yMzA5MTIxMzM0MDZaMBsxGTAXBgNV\n"
"BAMMEHNlcnZlckBkdW1teS5jb20wgZ8wDQYJKoZIhvcNAQEBBQADgY0AMIGJAoGB\n"
"AOk1ZcW8dRDTd1HqI4LAm9Lj8FSNbNRumYr660dCtONeYKiQw7hq5lj1/lEpGIyT\n"
"UCCTVO7ddBVClyrKSn3ig5YTM1t0zhf1bAvu4WW9PTM4q/dvvHVfPcBH7piXlJbi\n"
"SoLfWZg1BKvdj26vLJnlbWbSJa18QkVEkNkPnSrLeSyrAgMBAAEwDQYJKoZIhvcN\n"
"AQEFBQADgYEAWkf4rPXROOi/lJZrucZ91gBqk+edKXGoDBX+y5bgvLsJO3nHXq++\n"
"uSxfEdUiIV8IfqBP4QghyldReCIrwqhl4Yq8gSpS4yZ9tmXc7KaGHB3E+E034Eiv\n"
"k6x/qHhpZvOdHLt3B5Osb3Y1sg5zjQnx8mvmJRfNp4SOOgIs5M7Khpo=\n"
"-----END CERTIFICATE-----";

/*
 * PEM-encoded client certificate.
 *
 * Certificate for P-256 elliptic curve key.
 */
 //ce52dde4e7d-certificate.pem
static const char tlstestCLIENT_CERTIFICATE_PEM_EC[] =
"-----BEGIN CERTIFICATE-----\n"
"MIIC4zCCAcugAwIBAgIVAN5TqKAylMBHQP/hzUeoiecwM4zNMA0GCSqGSIb3DQEB\n"
"CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n"
"IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0xODA3MjQwNzIw\n"
"NDFaFw00OTEyMzEyMzU5NTlaMHIxCzAJBgNVBAYTAkNOMQswCQYDVQQIDAJTSDEM\n"
"MAoGA1UEBwwDVwgIMQ0wCwYDVQQKDARRQ09NMQwwCgYDVQQLDANJT0UxDTALBgNV\n"
"BAMMBFdMCAgxHDAaBgkqhkiG9w0BCQEWDWxlaUBhYWEuY29tCAgwWTATBgcqhkjO\n"
"PQIBBggqhkjOPQMBBwNCAAR1wHKM1/FDB7GZmUzG6VI7S+ZWvGnsTVjSgQU1Xgsd\n"
"Tpo+Gq+rViOLTunL5bj/GJ65U5Ah0wXTSSs6RDme5lTeo2AwXjAfBgNVHSMEGDAW\n"
"gBQRkAabHv+JcmIjYim2gIyZeTm01TAdBgNVHQ4EFgQU+WnNpOObAntEeeXVHAvR\n"
"ZWTnQJYwDAYDVR0TAQH/BAIwADAOBgNVHQ8BAf8EBAMCB4AwDQYJKoZIhvcNAQEL\n"
"BQADggEBALJr2tCecMIkOYVO8bKtrgu67MVWNymSV0IfTDlEpAhHX7kOap/LueCf\n"
"R/oDeiNT0LGBQZHpoy/5a/C3dl73jJQ2T6N68ckdyVcFbrK1AusQuCGrBiCHJepq\n"
"OAMufXJYY4clKVUpk/cxlHHkfE1ja3hXap4AcxLb2FcUUoLtAbIHpl++owVw0uFC\n"
"DkOq0rWZ4YwJ5RBpQuVWBby5XEGCnEK7tc/UT2Bn0tdKuhygNZ2u+tEw/wO02SnT\n"
"rwbctBAqreKiG6nJSYuuBzXql36xMcI9dGNQeVgeIVnHsr2aHDuma2Y5Fdmx0RKW\n"
"RAvU9p+G7pb9W4tUYsLwAtzzPn5CUvc=\n"
"-----END CERTIFICATE-----";

/*
 * PEM-encoded client private key.
 *
 * This is a P-256 elliptic curve key.
 */
static const char tlstestCLIENT_PRIVATE_KEY_PEM_EC[] = 
"-----BEGIN EC PRIVATE KEY-----\n"
"MHcCAQEEIDPF2ScJRGFj/+vU2L6HpFuea6fpiJWcHVLcKSm6OnqioAoGCCqGSM49\n"
"AwEHoUQDQgAEdcByjNfxQwexmZlMxulSO0vmVrxp7E1Y0oEFNV4LHU6aPhqvq1Yj\n"
"i07py+W4/xieuVOQIdMF00krOkQ5nuZU3g==\n"
"-----END EC PRIVATE KEY-----";


/* One character of this certificate has been changed in the issuer
 * name from Amazon Web Services to Amazon Web Cervices. */
 /* line 169: AOreMQqUI-->BOreMQqUI */
static const char tlstestCLIENT_CERTIFICATE_PEM_MALFORMED[] = 
"-----BEGIN CERTIFICATE-----\n"
"MIIDWjCCAkKgAwIBAgIVALTa0qLyaVsvOew7Q3AbfUS1w4F8MA0GCSqGSIb3DQEB\n"
"CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n"
"IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0xODA3MjAwMzU5\n"
"MjFaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\n"
"dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCuaUaYhuh8+voDIemr\n"
"5GSI60l33ZzPgqV2XVl8TYt+X1HB+PTF+51vTUrVNPon5R+OZzkoLEQomHpm0C2v\n"
"BLp1rDe+jq6jeWWHNx/lVxWLUrzW3oIg86CNdzhJzjlyAXJPppdV43sWkpfd2kEe\n"
"5D7zq8r/SxPysBtVvvACj3nK2cx+/v1SnO86QGvDavGIseHo86iOp1MX4f7vZFG+\n"
"eY8edVHVW824BhoEdDzCbRTeDfsRAiNYblXoqTU1LoZoWZ2CC4lABzRKs0Rvrv67\n"
"gZFnLjkblw6L/PbnWS38Owsbc3vhsnrP7JfvgpJNJKm1r8klI3CqIAz+dcNJ2EPI\n"
"F3nDAgMBAAGjYDBeMB8GA1UdIwQYMBaAFBGQBpse/4lyYiNiKbaAjJl5ObTVMB0G\n"
"A1UdDgQWBBTLou4ypc5dd5g8T6G2GbVKWuLOPzAMBgNVHRMBAf8EAjAAMA4GA1Ud\n"
"DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAElTvWZg7k8Wi614qSKo6Qs44\n"
"BOreMQqUIfcxzSmA4g2xAKqKutOzhYc+Itu/a6Ed8Sniu+8QYK34c8MyfpdLwxU1\n"
"0dl9N3XSahb+8psFMdSDRTaKq6tcmnU8PuykyHNOZ/fo5mtTH3hXyzwbGF8BapGn\n"
"xg8dWlTxvsT5f6tn2SOZFulyp/L3/QTgjnQkRl2j0zN7Qr/6qySeDFFOK9SSSH47\n"
"Bxi9Qwe1Jcf01F0Ku8/x00Gywah3U4b0zLpya/wThq3kqKYv6aXujoi/9qZkqJ/+\n"
"xiS+aGYgxvCDHW3UvmQNw6WPHpTTx90MDzRe3N0eF6VJm1ngtBAbC4V9cnJi/A==\n"
"-----END CERTIFICATE-----";


//server.pem from myself
/* Certificate which is not trusted by the broker. */
static const char tlstestCLIENT_UNTRUSTED_CERTIFICATE_PEM[] = 
"-----BEGIN CERTIFICATE-----\n"
"MIIBpTCCAQ4CAQEwDQYJKoZIhvcNAQEFBQAwGzEZMBcGA1UEAwwQY2EtaW50QGR1\n"
"bW15LmNvbTAeFw0xMzA5MTQxMzM0MDZaFw0yMzA5MTIxMzM0MDZaMBsxGTAXBgNV\n"
"BAMMEHNlcnZlckBkdW1teS5jb20wgZ8wDQYJKoZIhvcNAQEBBQADgY0AMIGJAoGB\n"
"AOk1ZcW8dRDTd1HqI4LAm9Lj8FSNbNRumYr660dCtONeYKiQw7hq5lj1/lEpGIyT\n"
"UCCTVO7ddBVClyrKSn3ig5YTM1t0zhf1bAvu4WW9PTM4q/dvvHVfPcBH7piXlJbi\n"
"SoLfWZg1BKvdj26vLJnlbWbSJa18QkVEkNkPnSrLeSyrAgMBAAEwDQYJKoZIhvcN\n"
"AQEFBQADgYEAWkf4rPXROOi/lJZrucZ91gBqk+edKXGoDBX+y5bgvLsJO3nHXq++\n"
"uSxfEdUiIV8IfqBP4QghyldReCIrwqhl4Yq8gSpS4yZ9tmXc7KaGHB3E+E034Eiv\n"
"k6x/qHhpZvOdHLt3B5Osb3Y1sg5zjQnx8mvmJRfNp4SOOgIs5M7Khpo=\n"
"-----END CERTIFICATE-----";


//server.key from myself
/* Private key corresponding to the untrusted certificate. */
static const char tlstestCLIENT_UNTRUSTED_PRIVATE_KEY_PEM[] = 
"-----BEGIN RSA PRIVATE KEY-----\n"
"MIICXQIBAAKBgQDpNWXFvHUQ03dR6iOCwJvS4/BUjWzUbpmK+utHQrTjXmCokMO4\n"
"auZY9f5RKRiMk1Agk1Tu3XQVQpcqykp94oOWEzNbdM4X9WwL7uFlvT0zOKv3b7x1\n"
"Xz3AR+6Yl5SW4kqC31mYNQSr3Y9uryyZ5W1m0iWtfEJFRJDZD50qy3ksqwIDAQAB\n"
"AoGBAMBDA4qHmkOq8z4XN/t963lr7iDnD4f7Pp6zyvDO7+5bSnjuEE2j5BAHjgk/\n"
"Rjvu3ypcDLN441D7u0DN0agC7NNkKoxG5Z23OhhtcPTIkqHRoFA9UGZAgxvfTUET\n"
"g/1AOpmC0FCkTftoMVTl4LZ1jMNr/Go4d/ZLW3B2uaauduCRAkEA+06/yGWoKquE\n"
"ObPrGQbJd8TS6+qB8i1nY9z4VmAwMusUX60vrRK1LyT1jjsDu64pWi2Pu0OoRgbU\n"
"XXYIHahbTwJBAO2QIo+BiUnbgrJutlgGyxKzc1SUAcTJyRZc/38blrgNv3TyfM6k\n"
"7svYdVxjzUQapKH1hzq+gMcAEus/HPRs0eUCQDDKlUmfEwtVyZI6cEannq32NM1A\n"
"9oHCdvRYjo6WlkUMhyQcR8lefHbuwg4fPxZNNhIgDmvZMu6FnO2YYPMBINkCQQDE\n"
"b22Uekk6cC9XOeK/UQa0NPyFkEkSHsSPIGEICpkLIhsRKb135burhRYuSjweN2Ww\n"
"omSqd4HmizIZobtghWbdAkApMlkCjqzDnd+zp1iha2+waR17niKjCDO9xyGGFBge\n"
"pYZmsu28HsWtRrbDIS57WJYWSFSQHMf2G8t3GsLn6nqK\n"
"-----END RSA PRIVATE KEY-----";

/* Device certificate created using BYOC instructions. */
/*AWS IOT:b966ebda03652b8937809ee18c4b6530e75f5c8bfb27823e7b46aa9b2ce18f62*/
static const char tlstestCLIENT_BYOC_CERTIFICATE_PEM[] = 
"-----BEGIN CERTIFICATE-----\n"
"MIIDwDCCAqgCCQDg6SB4NAfk9DANBgkqhkiG9w0BAQsFADCBgjELMAkGA1UEBhMC\n"
"VVMxCzAJBgNVBAgMAldBMQ4wDAYDVQQHDAVQbGFjZTEUMBIGA1UECgwLWW91ckNv\n"
"bXBhbnkxCzAJBgNVBAsMAklUMRYwFAYDVQQDDA13d3cueW91cnMuY29tMRswGQYJ\n"
"KoZIhvcNAQkBFgxsZWlAeW91ci5jb20wHhcNMTgwNzI0MDgwNDQxWhcNMTkxMjA2\n"
"MDgwNDQxWjCBwDELMAkGA1UEBhMCQVUxCzAJBgNVBAgMAlNIMQswCQYDVQQHDAJT\n"
"SDEhMB8GA1UECgwYSW50ZXJuZXQgV2lkZ2l0cyBQdHkgTHRkMQwwCgYDVQQLDANJ\n"
"T0UxSTBHBgNVBAMMQDU2Zjk4YWFmMzUxN2MwNTk4ZmFjYzE3OGZkZWE5NDdkMTky\n"
"OGM3NWUzOGZmMTBlNDdiODFkZDE3ODIxYjJlYTgxGzAZBgkqhkiG9w0BCQEWDGxl\n"
"aUBib3NzLmNvbTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALnFs4P2\n"
"lnPqcKpSvk4TPZ72MEWOHcQqJapgIaCPGbf3Rm5wI6YLufYw3BstU3OO0bQPcHzh\n"
"Zv8mn+YM3MGIGjyGfKlzTNJCcHlt6fWwyTUGAD3ajjmAUKcZYoZy/tLdLXkUT/05\n"
"gG0Dt7X9E0Usjg0PkZr48oCevJ9Ex14cQrZ97O/6FgjEfpvTVGnmhPrivasWt4Ou\n"
"7b3P+lyeDddSrtb2VDT2pF7xjMD/IuBv/JPNAGVNzTRu/Q7KqxMbFrEIIJWLWdAX\n"
"mrlXJ0HYW6kkIK7F4eWrRYkf+OvnVj1NYsAxwWa/ROAXkBQnJqFIu32nFO/kG5PG\n"
"37EhMgDcGJybi/UCAwEAATANBgkqhkiG9w0BAQsFAAOCAQEAIYGhkyox/qLt8S9N\n"
"vAS7IfkbitXyqN4T/jtRLFUvq9KWqjl2i7CRWIjh7NRqRL53DsYuYBQuZ2DL3Izr\n"
"MqQV0sly1jAzLLIrHbCokKF0vjzSNJaMLgXc41LUwQWx76Alai/RROnQIeNhYXMX\n"
"HsaB95coPhtie/lEXePnI+UktLFgQHHB1w7uxQj9jIW11BJBMzEqhWeN+mD4EtHD\n"
"KvlmAyHxElZLzEs6y9MlqEyXVpE/k1h0qN10WSrvw5Mxc4Lrp8eZ4eWAWtMhytLn\n"
"DEPSPDUNKqBiLdhlb9IjlTe6a5C6tl0LObC9gGsxq1SkVDiwFFVBeMqjLWEYpu/k\n"
"EPJ38g==\n"
"-----END CERTIFICATE-----";

/* Device private key created using BYOC instructions. */
static const char tlstestCLIENT_BYOC_PRIVATE_KEY_PEM[] = 
"-----BEGIN RSA PRIVATE KEY-----\n"
"MIIEpAIBAAKCAQEAucWzg/aWc+pwqlK+ThM9nvYwRY4dxColqmAhoI8Zt/dGbnAj\n"
"pgu59jDcGy1Tc47RtA9wfOFm/yaf5gzcwYgaPIZ8qXNM0kJweW3p9bDJNQYAPdqO\n"
"OYBQpxlihnL+0t0teRRP/TmAbQO3tf0TRSyODQ+RmvjygJ68n0THXhxCtn3s7/oW\n"
"CMR+m9NUaeaE+uK9qxa3g67tvc/6XJ4N11Ku1vZUNPakXvGMwP8i4G/8k80AZU3N\n"
"NG79DsqrExsWsQgglYtZ0BeauVcnQdhbqSQgrsXh5atFiR/46+dWPU1iwDHBZr9E\n"
"4BeQFCcmoUi7facU7+Qbk8bfsSEyANwYnJuL9QIDAQABAoIBAA+5+NR3D42Ijzkc\n"
"ABhD8LeAR93bhhGRL9cYhEA/XQIB4OiAfcQUwg1hXYC/eY0SzhXcKL2ppzp6Xpbv\n"
"B9EqYG43RF5j8GDsVvEwqNmvuZjPhT23PssHXcyHjZusKH5ZUvwpCAx7za9s3SR+\n"
"5B67AtuAMedYo87XoUgqXmZNJiiko0yqG1ZhZapbVwBX7LTAmBd+cqrSAPVOveaN\n"
"NaPY/6pK+v/xQCSSKWbu7Th4VpwK5w4ng4Wm2ZOWJSObP7GesJFiCmb0AvLidENV\n"
"IQlj7fcc5Ry6Ubxzdl4G4OmZ8mrzpnTG/jT2WlHh4cu+mx5i23cnfJ8vf3MIVb7d\n"
"eS0+yAECgYEA8H7PqnakI9OTmPhHziLzIuKOxX3oJfAtlePYKI+eQ7OuXBU52nGo\n"
"z3lyecSYIU/xJmbt+QCGf18hfXhDrcr4hE8Tx5zKyaxq/UdqcNtzR+KojCy8ayKU\n"
"0+XG2KugBmjaRxZwJQUyl1PToPdDIUAamzRMZTPKb9Bdz/9q0gxrM4ECgYEAxb+6\n"
"YrBctQx+bHZIp9yswD9HD64TBL5UK7+wef7crW52ymZqppb7rqXZnp21kZqJkxHS\n"
"AELu/I8BL16nRN4DsmuhS0d90yG23L6/qkWeDOP6EkdytSyIbjrbU0e3guADbtm/\n"
"Y/a9IzEW/2ftSqUAfDlVdjSbOyiSQEQb0Tw2AnUCgYEA38TujuqzUU6FEBk8HrZw\n"
"Sm5Jb8L2JY6zq7sDnsH6/X2LZ8ysNu/4pYuYE2r0LlLGy/eLx1tQyeUHMUqclnG8\n"
"CMfXXK0sFrhiGGbByF64hhOExmC9tGXJ2tv6yBHw5OXc67YaBKgwaZOq3yQShzax\n"
"SuY/iw7EdoOHNoiuqOC7QoECgYEApsaUgzcKeQcYeJEppajPaTP00pyVHaMHif4Y\n"
"8EqqAvru5LSLrgQYL6tgZg3MXAhhjs+wtNe+hvJ0pWbG26YCqC9t0PdyfuYoOvQE\n"
"4a3lJin/dfscGwB777tjzlDlzFLxkkPCzqQBz/RO2Qjlb9bJGfugwBiN8s68ycan\n"
"T0fgpSECgYA6ov8c9qHpGbuMgQdpO1KHK4om1DyxbY4aeKTZb1rp7pUptbxmreDG\n"
"/aXOy51p8yALsG/jzD6da6MiSf1C7ZLPMd6A/u+3ZWAL7RwgcNpkd+9bV2iyZTav\n"
"Yd5CNkzvCNUbLDdV0s7WYWE5Vc3k0/G2o6kS3svm4ttURgVxM9QCGA==\n"
"-----END RSA PRIVATE KEY-----";