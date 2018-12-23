/* clang-format off */
/*
 * Generated file - do not edit.
 * Command: /mongoose-os/fw/tools/gen_sys_config.py --c_name=mgos_config --c_global_name=mgos_sys_config --dest_dir=/fwbuild-volumes/2.10.0/apps/mbed/esp32/build_contexts/build_ctx_353438658/build/gen/ /mongoose-os/fw/src/mgos_debug_udp_config.yaml /mongoose-os/fw/src/mgos_sys_config.yaml /mongoose-os/fw/platforms/esp32/src/esp32_sys_config.yaml /fwbuild-volumes/2.10.0/apps/mbed/esp32/build_contexts/build_ctx_353438658/build/gen/mos_conf_schema.yml
 */

#ifndef MGOS_CONFIG_H_
#define MGOS_CONFIG_H_

#include "mgos_config_util.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct mgos_config_debug {
  char *udp_log_addr;
  int level;
  char *filter;
  int stdout_uart;
  int stderr_uart;
  int factory_reset_gpio;
  char *mg_mgr_hexdump_file;
  int mbedtls_level;
};

struct mgos_config_device {
  char *id;
  char *license;
};

struct mgos_config_sys_mount {
  char *path;
  char *dev_type;
  char *dev_opts;
  char *fs_type;
  char *fs_opts;
};

struct mgos_config_sys_atca {
  int enable;
  int i2c_addr;
  int ecdh_slots_mask;
};

struct mgos_config_sys {
  struct mgos_config_sys_mount mount;
  char *tz_spec;
  int wdt_timeout;
  char *pref_ota_lib;
  struct mgos_config_sys_atca atca;
};

struct mgos_config_i2c {
  int enable;
  int freq;
  int debug;
  int unit_no;
  int sda_gpio;
  int scl_gpio;
};

struct mgos_config_rpc_uart {
  int uart_no;
  int baud_rate;
  int fc_type;
};

struct mgos_config_rpc {
  int enable;
  int max_frame_size;
  int max_queue_length;
  int default_out_channel_idle_close_timeout;
  char *acl_file;
  char *auth_domain;
  char *auth_file;
  struct mgos_config_rpc_uart uart;
};

struct mgos_config_wifi_ap {
  int enable;
  char *ssid;
  char *pass;
  int hidden;
  int channel;
  int max_connections;
  char *ip;
  char *netmask;
  char *gw;
  char *dhcp_start;
  char *dhcp_end;
  int trigger_on_gpio;
  int disable_after;
  char *hostname;
  int keep_enabled;
};

struct mgos_config_wifi_sta {
  int enable;
  char *ssid;
  char *pass;
  char *user;
  char *anon_identity;
  char *cert;
  char *key;
  char *ca_cert;
  char *ip;
  char *netmask;
  char *gw;
  char *nameserver;
  char *dhcp_hostname;
};

struct mgos_config_wifi_sta1 {
  int enable;
  char *ssid;
  char *pass;
  char *user;
  char *anon_identity;
  char *cert;
  char *key;
  char *ca_cert;
  char *ip;
  char *netmask;
  char *gw;
  char *nameserver;
  char *dhcp_hostname;
};

struct mgos_config_wifi_sta2 {
  int enable;
  char *ssid;
  char *pass;
  char *user;
  char *anon_identity;
  char *cert;
  char *key;
  char *ca_cert;
  char *ip;
  char *netmask;
  char *gw;
  char *nameserver;
  char *dhcp_hostname;
};

struct mgos_config_wifi {
  struct mgos_config_wifi_ap ap;
  struct mgos_config_wifi_sta sta;
  struct mgos_config_wifi_sta1 sta1;
  struct mgos_config_wifi_sta2 sta2;
  int sta_cfg_idx;
  int sta_connect_timeout;
};

struct mgos_config_board_led1 {
  int pin;
  int active_high;
};

struct mgos_config_board_led2 {
  int pin;
  int active_high;
};

struct mgos_config_board_led3 {
  int pin;
  int active_high;
};

struct mgos_config_board_btn1 {
  int pin;
  int pull_up;
};

struct mgos_config_board_btn2 {
  int pin;
  int pull_up;
};

struct mgos_config_board_btn3 {
  int pin;
  int pull_up;
};

struct mgos_config_board {
  struct mgos_config_board_led1 led1;
  struct mgos_config_board_led2 led2;
  struct mgos_config_board_led3 led3;
  struct mgos_config_board_btn1 btn1;
  struct mgos_config_board_btn2 btn2;
  struct mgos_config_board_btn3 btn3;
};

struct mgos_config {
  struct mgos_config_debug debug;
  struct mgos_config_device device;
  struct mgos_config_sys sys;
  char *conf_acl;
  struct mgos_config_i2c i2c;
  struct mgos_config_rpc rpc;
  struct mgos_config_wifi wifi;
  struct mgos_config_board board;
};


const struct mgos_conf_entry *mgos_config_schema();

/* Parametrized accessor prototypes {{{ */
const struct mgos_config_debug *mgos_config_get_debug(struct mgos_config *cfg);
const char *mgos_config_get_debug_udp_log_addr(struct mgos_config *cfg);
int         mgos_config_get_debug_level(struct mgos_config *cfg);
const char *mgos_config_get_debug_filter(struct mgos_config *cfg);
int         mgos_config_get_debug_stdout_uart(struct mgos_config *cfg);
int         mgos_config_get_debug_stderr_uart(struct mgos_config *cfg);
int         mgos_config_get_debug_factory_reset_gpio(struct mgos_config *cfg);
const char *mgos_config_get_debug_mg_mgr_hexdump_file(struct mgos_config *cfg);
int         mgos_config_get_debug_mbedtls_level(struct mgos_config *cfg);
const struct mgos_config_device *mgos_config_get_device(struct mgos_config *cfg);
const char *mgos_config_get_device_id(struct mgos_config *cfg);
const char *mgos_config_get_device_license(struct mgos_config *cfg);
const struct mgos_config_sys *mgos_config_get_sys(struct mgos_config *cfg);
const struct mgos_config_sys_mount *mgos_config_get_sys_mount(struct mgos_config *cfg);
const char *mgos_config_get_sys_mount_path(struct mgos_config *cfg);
const char *mgos_config_get_sys_mount_dev_type(struct mgos_config *cfg);
const char *mgos_config_get_sys_mount_dev_opts(struct mgos_config *cfg);
const char *mgos_config_get_sys_mount_fs_type(struct mgos_config *cfg);
const char *mgos_config_get_sys_mount_fs_opts(struct mgos_config *cfg);
const char *mgos_config_get_sys_tz_spec(struct mgos_config *cfg);
int         mgos_config_get_sys_wdt_timeout(struct mgos_config *cfg);
const char *mgos_config_get_sys_pref_ota_lib(struct mgos_config *cfg);
const struct mgos_config_sys_atca *mgos_config_get_sys_atca(struct mgos_config *cfg);
int         mgos_config_get_sys_atca_enable(struct mgos_config *cfg);
int         mgos_config_get_sys_atca_i2c_addr(struct mgos_config *cfg);
int         mgos_config_get_sys_atca_ecdh_slots_mask(struct mgos_config *cfg);
const char *mgos_config_get_conf_acl(struct mgos_config *cfg);
const struct mgos_config_i2c *mgos_config_get_i2c(struct mgos_config *cfg);
int         mgos_config_get_i2c_enable(struct mgos_config *cfg);
int         mgos_config_get_i2c_freq(struct mgos_config *cfg);
int         mgos_config_get_i2c_debug(struct mgos_config *cfg);
int         mgos_config_get_i2c_unit_no(struct mgos_config *cfg);
int         mgos_config_get_i2c_sda_gpio(struct mgos_config *cfg);
int         mgos_config_get_i2c_scl_gpio(struct mgos_config *cfg);
const struct mgos_config_rpc *mgos_config_get_rpc(struct mgos_config *cfg);
int         mgos_config_get_rpc_enable(struct mgos_config *cfg);
int         mgos_config_get_rpc_max_frame_size(struct mgos_config *cfg);
int         mgos_config_get_rpc_max_queue_length(struct mgos_config *cfg);
int         mgos_config_get_rpc_default_out_channel_idle_close_timeout(struct mgos_config *cfg);
const char *mgos_config_get_rpc_acl_file(struct mgos_config *cfg);
const char *mgos_config_get_rpc_auth_domain(struct mgos_config *cfg);
const char *mgos_config_get_rpc_auth_file(struct mgos_config *cfg);
const struct mgos_config_rpc_uart *mgos_config_get_rpc_uart(struct mgos_config *cfg);
int         mgos_config_get_rpc_uart_uart_no(struct mgos_config *cfg);
int         mgos_config_get_rpc_uart_baud_rate(struct mgos_config *cfg);
int         mgos_config_get_rpc_uart_fc_type(struct mgos_config *cfg);
const struct mgos_config_wifi *mgos_config_get_wifi(struct mgos_config *cfg);
const struct mgos_config_wifi_ap *mgos_config_get_wifi_ap(struct mgos_config *cfg);
int         mgos_config_get_wifi_ap_enable(struct mgos_config *cfg);
const char *mgos_config_get_wifi_ap_ssid(struct mgos_config *cfg);
const char *mgos_config_get_wifi_ap_pass(struct mgos_config *cfg);
int         mgos_config_get_wifi_ap_hidden(struct mgos_config *cfg);
int         mgos_config_get_wifi_ap_channel(struct mgos_config *cfg);
int         mgos_config_get_wifi_ap_max_connections(struct mgos_config *cfg);
const char *mgos_config_get_wifi_ap_ip(struct mgos_config *cfg);
const char *mgos_config_get_wifi_ap_netmask(struct mgos_config *cfg);
const char *mgos_config_get_wifi_ap_gw(struct mgos_config *cfg);
const char *mgos_config_get_wifi_ap_dhcp_start(struct mgos_config *cfg);
const char *mgos_config_get_wifi_ap_dhcp_end(struct mgos_config *cfg);
int         mgos_config_get_wifi_ap_trigger_on_gpio(struct mgos_config *cfg);
int         mgos_config_get_wifi_ap_disable_after(struct mgos_config *cfg);
const char *mgos_config_get_wifi_ap_hostname(struct mgos_config *cfg);
int         mgos_config_get_wifi_ap_keep_enabled(struct mgos_config *cfg);
const struct mgos_config_wifi_sta *mgos_config_get_wifi_sta(struct mgos_config *cfg);
int         mgos_config_get_wifi_sta_enable(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta_ssid(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta_pass(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta_user(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta_anon_identity(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta_cert(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta_key(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta_ca_cert(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta_ip(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta_netmask(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta_gw(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta_nameserver(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta_dhcp_hostname(struct mgos_config *cfg);
const struct mgos_config_wifi_sta1 *mgos_config_get_wifi_sta1(struct mgos_config *cfg);
int         mgos_config_get_wifi_sta1_enable(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta1_ssid(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta1_pass(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta1_user(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta1_anon_identity(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta1_cert(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta1_key(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta1_ca_cert(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta1_ip(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta1_netmask(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta1_gw(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta1_nameserver(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta1_dhcp_hostname(struct mgos_config *cfg);
const struct mgos_config_wifi_sta2 *mgos_config_get_wifi_sta2(struct mgos_config *cfg);
int         mgos_config_get_wifi_sta2_enable(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta2_ssid(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta2_pass(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta2_user(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta2_anon_identity(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta2_cert(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta2_key(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta2_ca_cert(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta2_ip(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta2_netmask(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta2_gw(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta2_nameserver(struct mgos_config *cfg);
const char *mgos_config_get_wifi_sta2_dhcp_hostname(struct mgos_config *cfg);
int         mgos_config_get_wifi_sta_cfg_idx(struct mgos_config *cfg);
int         mgos_config_get_wifi_sta_connect_timeout(struct mgos_config *cfg);
const struct mgos_config_board *mgos_config_get_board(struct mgos_config *cfg);
const struct mgos_config_board_led1 *mgos_config_get_board_led1(struct mgos_config *cfg);
int         mgos_config_get_board_led1_pin(struct mgos_config *cfg);
int         mgos_config_get_board_led1_active_high(struct mgos_config *cfg);
const struct mgos_config_board_led2 *mgos_config_get_board_led2(struct mgos_config *cfg);
int         mgos_config_get_board_led2_pin(struct mgos_config *cfg);
int         mgos_config_get_board_led2_active_high(struct mgos_config *cfg);
const struct mgos_config_board_led3 *mgos_config_get_board_led3(struct mgos_config *cfg);
int         mgos_config_get_board_led3_pin(struct mgos_config *cfg);
int         mgos_config_get_board_led3_active_high(struct mgos_config *cfg);
const struct mgos_config_board_btn1 *mgos_config_get_board_btn1(struct mgos_config *cfg);
int         mgos_config_get_board_btn1_pin(struct mgos_config *cfg);
int         mgos_config_get_board_btn1_pull_up(struct mgos_config *cfg);
const struct mgos_config_board_btn2 *mgos_config_get_board_btn2(struct mgos_config *cfg);
int         mgos_config_get_board_btn2_pin(struct mgos_config *cfg);
int         mgos_config_get_board_btn2_pull_up(struct mgos_config *cfg);
const struct mgos_config_board_btn3 *mgos_config_get_board_btn3(struct mgos_config *cfg);
int         mgos_config_get_board_btn3_pin(struct mgos_config *cfg);
int         mgos_config_get_board_btn3_pull_up(struct mgos_config *cfg);

void mgos_config_set_debug_udp_log_addr(struct mgos_config *cfg, const char *val);
void mgos_config_set_debug_level(struct mgos_config *cfg, int         val);
void mgos_config_set_debug_filter(struct mgos_config *cfg, const char *val);
void mgos_config_set_debug_stdout_uart(struct mgos_config *cfg, int         val);
void mgos_config_set_debug_stderr_uart(struct mgos_config *cfg, int         val);
void mgos_config_set_debug_factory_reset_gpio(struct mgos_config *cfg, int         val);
void mgos_config_set_debug_mg_mgr_hexdump_file(struct mgos_config *cfg, const char *val);
void mgos_config_set_debug_mbedtls_level(struct mgos_config *cfg, int         val);
void mgos_config_set_device_id(struct mgos_config *cfg, const char *val);
void mgos_config_set_device_license(struct mgos_config *cfg, const char *val);
void mgos_config_set_sys_mount_path(struct mgos_config *cfg, const char *val);
void mgos_config_set_sys_mount_dev_type(struct mgos_config *cfg, const char *val);
void mgos_config_set_sys_mount_dev_opts(struct mgos_config *cfg, const char *val);
void mgos_config_set_sys_mount_fs_type(struct mgos_config *cfg, const char *val);
void mgos_config_set_sys_mount_fs_opts(struct mgos_config *cfg, const char *val);
void mgos_config_set_sys_tz_spec(struct mgos_config *cfg, const char *val);
void mgos_config_set_sys_wdt_timeout(struct mgos_config *cfg, int         val);
void mgos_config_set_sys_pref_ota_lib(struct mgos_config *cfg, const char *val);
void mgos_config_set_sys_atca_enable(struct mgos_config *cfg, int         val);
void mgos_config_set_sys_atca_i2c_addr(struct mgos_config *cfg, int         val);
void mgos_config_set_sys_atca_ecdh_slots_mask(struct mgos_config *cfg, int         val);
void mgos_config_set_conf_acl(struct mgos_config *cfg, const char *val);
void mgos_config_set_i2c_enable(struct mgos_config *cfg, int         val);
void mgos_config_set_i2c_freq(struct mgos_config *cfg, int         val);
void mgos_config_set_i2c_debug(struct mgos_config *cfg, int         val);
void mgos_config_set_i2c_unit_no(struct mgos_config *cfg, int         val);
void mgos_config_set_i2c_sda_gpio(struct mgos_config *cfg, int         val);
void mgos_config_set_i2c_scl_gpio(struct mgos_config *cfg, int         val);
void mgos_config_set_rpc_enable(struct mgos_config *cfg, int         val);
void mgos_config_set_rpc_max_frame_size(struct mgos_config *cfg, int         val);
void mgos_config_set_rpc_max_queue_length(struct mgos_config *cfg, int         val);
void mgos_config_set_rpc_default_out_channel_idle_close_timeout(struct mgos_config *cfg, int         val);
void mgos_config_set_rpc_acl_file(struct mgos_config *cfg, const char *val);
void mgos_config_set_rpc_auth_domain(struct mgos_config *cfg, const char *val);
void mgos_config_set_rpc_auth_file(struct mgos_config *cfg, const char *val);
void mgos_config_set_rpc_uart_uart_no(struct mgos_config *cfg, int         val);
void mgos_config_set_rpc_uart_baud_rate(struct mgos_config *cfg, int         val);
void mgos_config_set_rpc_uart_fc_type(struct mgos_config *cfg, int         val);
void mgos_config_set_wifi_ap_enable(struct mgos_config *cfg, int         val);
void mgos_config_set_wifi_ap_ssid(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_ap_pass(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_ap_hidden(struct mgos_config *cfg, int         val);
void mgos_config_set_wifi_ap_channel(struct mgos_config *cfg, int         val);
void mgos_config_set_wifi_ap_max_connections(struct mgos_config *cfg, int         val);
void mgos_config_set_wifi_ap_ip(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_ap_netmask(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_ap_gw(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_ap_dhcp_start(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_ap_dhcp_end(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_ap_trigger_on_gpio(struct mgos_config *cfg, int         val);
void mgos_config_set_wifi_ap_disable_after(struct mgos_config *cfg, int         val);
void mgos_config_set_wifi_ap_hostname(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_ap_keep_enabled(struct mgos_config *cfg, int         val);
void mgos_config_set_wifi_sta_enable(struct mgos_config *cfg, int         val);
void mgos_config_set_wifi_sta_ssid(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta_pass(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta_user(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta_anon_identity(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta_cert(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta_key(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta_ca_cert(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta_ip(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta_netmask(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta_gw(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta_nameserver(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta_dhcp_hostname(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta1_enable(struct mgos_config *cfg, int         val);
void mgos_config_set_wifi_sta1_ssid(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta1_pass(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta1_user(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta1_anon_identity(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta1_cert(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta1_key(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta1_ca_cert(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta1_ip(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta1_netmask(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta1_gw(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta1_nameserver(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta1_dhcp_hostname(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta2_enable(struct mgos_config *cfg, int         val);
void mgos_config_set_wifi_sta2_ssid(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta2_pass(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta2_user(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta2_anon_identity(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta2_cert(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta2_key(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta2_ca_cert(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta2_ip(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta2_netmask(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta2_gw(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta2_nameserver(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta2_dhcp_hostname(struct mgos_config *cfg, const char *val);
void mgos_config_set_wifi_sta_cfg_idx(struct mgos_config *cfg, int         val);
void mgos_config_set_wifi_sta_connect_timeout(struct mgos_config *cfg, int         val);
void mgos_config_set_board_led1_pin(struct mgos_config *cfg, int         val);
void mgos_config_set_board_led1_active_high(struct mgos_config *cfg, int         val);
void mgos_config_set_board_led2_pin(struct mgos_config *cfg, int         val);
void mgos_config_set_board_led2_active_high(struct mgos_config *cfg, int         val);
void mgos_config_set_board_led3_pin(struct mgos_config *cfg, int         val);
void mgos_config_set_board_led3_active_high(struct mgos_config *cfg, int         val);
void mgos_config_set_board_btn1_pin(struct mgos_config *cfg, int         val);
void mgos_config_set_board_btn1_pull_up(struct mgos_config *cfg, int         val);
void mgos_config_set_board_btn2_pin(struct mgos_config *cfg, int         val);
void mgos_config_set_board_btn2_pull_up(struct mgos_config *cfg, int         val);
void mgos_config_set_board_btn3_pin(struct mgos_config *cfg, int         val);
void mgos_config_set_board_btn3_pull_up(struct mgos_config *cfg, int         val);
/* }}} */

extern struct mgos_config mgos_sys_config;

static inline bool mgos_sys_config_get(const struct mg_str key, struct mg_str *value) { return mgos_config_get(key, value, &mgos_sys_config, mgos_config_schema()); }
static inline bool mgos_sys_config_set(const struct mg_str key, const struct mg_str value, bool free_strings) { return mgos_config_set(key, value, &mgos_sys_config, mgos_config_schema(), free_strings); }

static inline const struct mgos_config_debug *mgos_sys_config_get_debug(void) { return mgos_config_get_debug(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_debug_udp_log_addr(void) { return mgos_config_get_debug_udp_log_addr(&mgos_sys_config); }
static inline int         mgos_sys_config_get_debug_level(void) { return mgos_config_get_debug_level(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_debug_filter(void) { return mgos_config_get_debug_filter(&mgos_sys_config); }
static inline int         mgos_sys_config_get_debug_stdout_uart(void) { return mgos_config_get_debug_stdout_uart(&mgos_sys_config); }
static inline int         mgos_sys_config_get_debug_stderr_uart(void) { return mgos_config_get_debug_stderr_uart(&mgos_sys_config); }
static inline int         mgos_sys_config_get_debug_factory_reset_gpio(void) { return mgos_config_get_debug_factory_reset_gpio(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_debug_mg_mgr_hexdump_file(void) { return mgos_config_get_debug_mg_mgr_hexdump_file(&mgos_sys_config); }
static inline int         mgos_sys_config_get_debug_mbedtls_level(void) { return mgos_config_get_debug_mbedtls_level(&mgos_sys_config); }
static inline const struct mgos_config_device *mgos_sys_config_get_device(void) { return mgos_config_get_device(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_device_id(void) { return mgos_config_get_device_id(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_device_license(void) { return mgos_config_get_device_license(&mgos_sys_config); }
static inline const struct mgos_config_sys *mgos_sys_config_get_sys(void) { return mgos_config_get_sys(&mgos_sys_config); }
static inline const struct mgos_config_sys_mount *mgos_sys_config_get_sys_mount(void) { return mgos_config_get_sys_mount(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_sys_mount_path(void) { return mgos_config_get_sys_mount_path(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_sys_mount_dev_type(void) { return mgos_config_get_sys_mount_dev_type(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_sys_mount_dev_opts(void) { return mgos_config_get_sys_mount_dev_opts(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_sys_mount_fs_type(void) { return mgos_config_get_sys_mount_fs_type(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_sys_mount_fs_opts(void) { return mgos_config_get_sys_mount_fs_opts(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_sys_tz_spec(void) { return mgos_config_get_sys_tz_spec(&mgos_sys_config); }
static inline int         mgos_sys_config_get_sys_wdt_timeout(void) { return mgos_config_get_sys_wdt_timeout(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_sys_pref_ota_lib(void) { return mgos_config_get_sys_pref_ota_lib(&mgos_sys_config); }
static inline const struct mgos_config_sys_atca *mgos_sys_config_get_sys_atca(void) { return mgos_config_get_sys_atca(&mgos_sys_config); }
static inline int         mgos_sys_config_get_sys_atca_enable(void) { return mgos_config_get_sys_atca_enable(&mgos_sys_config); }
static inline int         mgos_sys_config_get_sys_atca_i2c_addr(void) { return mgos_config_get_sys_atca_i2c_addr(&mgos_sys_config); }
static inline int         mgos_sys_config_get_sys_atca_ecdh_slots_mask(void) { return mgos_config_get_sys_atca_ecdh_slots_mask(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_conf_acl(void) { return mgos_config_get_conf_acl(&mgos_sys_config); }
static inline const struct mgos_config_i2c *mgos_sys_config_get_i2c(void) { return mgos_config_get_i2c(&mgos_sys_config); }
static inline int         mgos_sys_config_get_i2c_enable(void) { return mgos_config_get_i2c_enable(&mgos_sys_config); }
static inline int         mgos_sys_config_get_i2c_freq(void) { return mgos_config_get_i2c_freq(&mgos_sys_config); }
static inline int         mgos_sys_config_get_i2c_debug(void) { return mgos_config_get_i2c_debug(&mgos_sys_config); }
static inline int         mgos_sys_config_get_i2c_unit_no(void) { return mgos_config_get_i2c_unit_no(&mgos_sys_config); }
static inline int         mgos_sys_config_get_i2c_sda_gpio(void) { return mgos_config_get_i2c_sda_gpio(&mgos_sys_config); }
static inline int         mgos_sys_config_get_i2c_scl_gpio(void) { return mgos_config_get_i2c_scl_gpio(&mgos_sys_config); }
static inline const struct mgos_config_rpc *mgos_sys_config_get_rpc(void) { return mgos_config_get_rpc(&mgos_sys_config); }
static inline int         mgos_sys_config_get_rpc_enable(void) { return mgos_config_get_rpc_enable(&mgos_sys_config); }
static inline int         mgos_sys_config_get_rpc_max_frame_size(void) { return mgos_config_get_rpc_max_frame_size(&mgos_sys_config); }
static inline int         mgos_sys_config_get_rpc_max_queue_length(void) { return mgos_config_get_rpc_max_queue_length(&mgos_sys_config); }
static inline int         mgos_sys_config_get_rpc_default_out_channel_idle_close_timeout(void) { return mgos_config_get_rpc_default_out_channel_idle_close_timeout(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_rpc_acl_file(void) { return mgos_config_get_rpc_acl_file(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_rpc_auth_domain(void) { return mgos_config_get_rpc_auth_domain(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_rpc_auth_file(void) { return mgos_config_get_rpc_auth_file(&mgos_sys_config); }
static inline const struct mgos_config_rpc_uart *mgos_sys_config_get_rpc_uart(void) { return mgos_config_get_rpc_uart(&mgos_sys_config); }
static inline int         mgos_sys_config_get_rpc_uart_uart_no(void) { return mgos_config_get_rpc_uart_uart_no(&mgos_sys_config); }
static inline int         mgos_sys_config_get_rpc_uart_baud_rate(void) { return mgos_config_get_rpc_uart_baud_rate(&mgos_sys_config); }
static inline int         mgos_sys_config_get_rpc_uart_fc_type(void) { return mgos_config_get_rpc_uart_fc_type(&mgos_sys_config); }
static inline const struct mgos_config_wifi *mgos_sys_config_get_wifi(void) { return mgos_config_get_wifi(&mgos_sys_config); }
static inline const struct mgos_config_wifi_ap *mgos_sys_config_get_wifi_ap(void) { return mgos_config_get_wifi_ap(&mgos_sys_config); }
static inline int         mgos_sys_config_get_wifi_ap_enable(void) { return mgos_config_get_wifi_ap_enable(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_ap_ssid(void) { return mgos_config_get_wifi_ap_ssid(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_ap_pass(void) { return mgos_config_get_wifi_ap_pass(&mgos_sys_config); }
static inline int         mgos_sys_config_get_wifi_ap_hidden(void) { return mgos_config_get_wifi_ap_hidden(&mgos_sys_config); }
static inline int         mgos_sys_config_get_wifi_ap_channel(void) { return mgos_config_get_wifi_ap_channel(&mgos_sys_config); }
static inline int         mgos_sys_config_get_wifi_ap_max_connections(void) { return mgos_config_get_wifi_ap_max_connections(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_ap_ip(void) { return mgos_config_get_wifi_ap_ip(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_ap_netmask(void) { return mgos_config_get_wifi_ap_netmask(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_ap_gw(void) { return mgos_config_get_wifi_ap_gw(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_ap_dhcp_start(void) { return mgos_config_get_wifi_ap_dhcp_start(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_ap_dhcp_end(void) { return mgos_config_get_wifi_ap_dhcp_end(&mgos_sys_config); }
static inline int         mgos_sys_config_get_wifi_ap_trigger_on_gpio(void) { return mgos_config_get_wifi_ap_trigger_on_gpio(&mgos_sys_config); }
static inline int         mgos_sys_config_get_wifi_ap_disable_after(void) { return mgos_config_get_wifi_ap_disable_after(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_ap_hostname(void) { return mgos_config_get_wifi_ap_hostname(&mgos_sys_config); }
static inline int         mgos_sys_config_get_wifi_ap_keep_enabled(void) { return mgos_config_get_wifi_ap_keep_enabled(&mgos_sys_config); }
static inline const struct mgos_config_wifi_sta *mgos_sys_config_get_wifi_sta(void) { return mgos_config_get_wifi_sta(&mgos_sys_config); }
static inline int         mgos_sys_config_get_wifi_sta_enable(void) { return mgos_config_get_wifi_sta_enable(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta_ssid(void) { return mgos_config_get_wifi_sta_ssid(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta_pass(void) { return mgos_config_get_wifi_sta_pass(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta_user(void) { return mgos_config_get_wifi_sta_user(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta_anon_identity(void) { return mgos_config_get_wifi_sta_anon_identity(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta_cert(void) { return mgos_config_get_wifi_sta_cert(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta_key(void) { return mgos_config_get_wifi_sta_key(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta_ca_cert(void) { return mgos_config_get_wifi_sta_ca_cert(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta_ip(void) { return mgos_config_get_wifi_sta_ip(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta_netmask(void) { return mgos_config_get_wifi_sta_netmask(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta_gw(void) { return mgos_config_get_wifi_sta_gw(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta_nameserver(void) { return mgos_config_get_wifi_sta_nameserver(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta_dhcp_hostname(void) { return mgos_config_get_wifi_sta_dhcp_hostname(&mgos_sys_config); }
static inline const struct mgos_config_wifi_sta1 *mgos_sys_config_get_wifi_sta1(void) { return mgos_config_get_wifi_sta1(&mgos_sys_config); }
static inline int         mgos_sys_config_get_wifi_sta1_enable(void) { return mgos_config_get_wifi_sta1_enable(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta1_ssid(void) { return mgos_config_get_wifi_sta1_ssid(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta1_pass(void) { return mgos_config_get_wifi_sta1_pass(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta1_user(void) { return mgos_config_get_wifi_sta1_user(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta1_anon_identity(void) { return mgos_config_get_wifi_sta1_anon_identity(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta1_cert(void) { return mgos_config_get_wifi_sta1_cert(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta1_key(void) { return mgos_config_get_wifi_sta1_key(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta1_ca_cert(void) { return mgos_config_get_wifi_sta1_ca_cert(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta1_ip(void) { return mgos_config_get_wifi_sta1_ip(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta1_netmask(void) { return mgos_config_get_wifi_sta1_netmask(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta1_gw(void) { return mgos_config_get_wifi_sta1_gw(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta1_nameserver(void) { return mgos_config_get_wifi_sta1_nameserver(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta1_dhcp_hostname(void) { return mgos_config_get_wifi_sta1_dhcp_hostname(&mgos_sys_config); }
static inline const struct mgos_config_wifi_sta2 *mgos_sys_config_get_wifi_sta2(void) { return mgos_config_get_wifi_sta2(&mgos_sys_config); }
static inline int         mgos_sys_config_get_wifi_sta2_enable(void) { return mgos_config_get_wifi_sta2_enable(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta2_ssid(void) { return mgos_config_get_wifi_sta2_ssid(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta2_pass(void) { return mgos_config_get_wifi_sta2_pass(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta2_user(void) { return mgos_config_get_wifi_sta2_user(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta2_anon_identity(void) { return mgos_config_get_wifi_sta2_anon_identity(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta2_cert(void) { return mgos_config_get_wifi_sta2_cert(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta2_key(void) { return mgos_config_get_wifi_sta2_key(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta2_ca_cert(void) { return mgos_config_get_wifi_sta2_ca_cert(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta2_ip(void) { return mgos_config_get_wifi_sta2_ip(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta2_netmask(void) { return mgos_config_get_wifi_sta2_netmask(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta2_gw(void) { return mgos_config_get_wifi_sta2_gw(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta2_nameserver(void) { return mgos_config_get_wifi_sta2_nameserver(&mgos_sys_config); }
static inline const char *mgos_sys_config_get_wifi_sta2_dhcp_hostname(void) { return mgos_config_get_wifi_sta2_dhcp_hostname(&mgos_sys_config); }
static inline int         mgos_sys_config_get_wifi_sta_cfg_idx(void) { return mgos_config_get_wifi_sta_cfg_idx(&mgos_sys_config); }
static inline int         mgos_sys_config_get_wifi_sta_connect_timeout(void) { return mgos_config_get_wifi_sta_connect_timeout(&mgos_sys_config); }
static inline const struct mgos_config_board *mgos_sys_config_get_board(void) { return mgos_config_get_board(&mgos_sys_config); }
static inline const struct mgos_config_board_led1 *mgos_sys_config_get_board_led1(void) { return mgos_config_get_board_led1(&mgos_sys_config); }
static inline int         mgos_sys_config_get_board_led1_pin(void) { return mgos_config_get_board_led1_pin(&mgos_sys_config); }
static inline int         mgos_sys_config_get_board_led1_active_high(void) { return mgos_config_get_board_led1_active_high(&mgos_sys_config); }
static inline const struct mgos_config_board_led2 *mgos_sys_config_get_board_led2(void) { return mgos_config_get_board_led2(&mgos_sys_config); }
static inline int         mgos_sys_config_get_board_led2_pin(void) { return mgos_config_get_board_led2_pin(&mgos_sys_config); }
static inline int         mgos_sys_config_get_board_led2_active_high(void) { return mgos_config_get_board_led2_active_high(&mgos_sys_config); }
static inline const struct mgos_config_board_led3 *mgos_sys_config_get_board_led3(void) { return mgos_config_get_board_led3(&mgos_sys_config); }
static inline int         mgos_sys_config_get_board_led3_pin(void) { return mgos_config_get_board_led3_pin(&mgos_sys_config); }
static inline int         mgos_sys_config_get_board_led3_active_high(void) { return mgos_config_get_board_led3_active_high(&mgos_sys_config); }
static inline const struct mgos_config_board_btn1 *mgos_sys_config_get_board_btn1(void) { return mgos_config_get_board_btn1(&mgos_sys_config); }
static inline int         mgos_sys_config_get_board_btn1_pin(void) { return mgos_config_get_board_btn1_pin(&mgos_sys_config); }
static inline int         mgos_sys_config_get_board_btn1_pull_up(void) { return mgos_config_get_board_btn1_pull_up(&mgos_sys_config); }
static inline const struct mgos_config_board_btn2 *mgos_sys_config_get_board_btn2(void) { return mgos_config_get_board_btn2(&mgos_sys_config); }
static inline int         mgos_sys_config_get_board_btn2_pin(void) { return mgos_config_get_board_btn2_pin(&mgos_sys_config); }
static inline int         mgos_sys_config_get_board_btn2_pull_up(void) { return mgos_config_get_board_btn2_pull_up(&mgos_sys_config); }
static inline const struct mgos_config_board_btn3 *mgos_sys_config_get_board_btn3(void) { return mgos_config_get_board_btn3(&mgos_sys_config); }
static inline int         mgos_sys_config_get_board_btn3_pin(void) { return mgos_config_get_board_btn3_pin(&mgos_sys_config); }
static inline int         mgos_sys_config_get_board_btn3_pull_up(void) { return mgos_config_get_board_btn3_pull_up(&mgos_sys_config); }

static inline void mgos_sys_config_set_debug_udp_log_addr(const char *val) { mgos_config_set_debug_udp_log_addr(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_debug_level(int         val) { mgos_config_set_debug_level(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_debug_filter(const char *val) { mgos_config_set_debug_filter(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_debug_stdout_uart(int         val) { mgos_config_set_debug_stdout_uart(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_debug_stderr_uart(int         val) { mgos_config_set_debug_stderr_uart(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_debug_factory_reset_gpio(int         val) { mgos_config_set_debug_factory_reset_gpio(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_debug_mg_mgr_hexdump_file(const char *val) { mgos_config_set_debug_mg_mgr_hexdump_file(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_debug_mbedtls_level(int         val) { mgos_config_set_debug_mbedtls_level(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_device_id(const char *val) { mgos_config_set_device_id(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_device_license(const char *val) { mgos_config_set_device_license(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_sys_mount_path(const char *val) { mgos_config_set_sys_mount_path(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_sys_mount_dev_type(const char *val) { mgos_config_set_sys_mount_dev_type(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_sys_mount_dev_opts(const char *val) { mgos_config_set_sys_mount_dev_opts(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_sys_mount_fs_type(const char *val) { mgos_config_set_sys_mount_fs_type(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_sys_mount_fs_opts(const char *val) { mgos_config_set_sys_mount_fs_opts(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_sys_tz_spec(const char *val) { mgos_config_set_sys_tz_spec(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_sys_wdt_timeout(int         val) { mgos_config_set_sys_wdt_timeout(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_sys_pref_ota_lib(const char *val) { mgos_config_set_sys_pref_ota_lib(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_sys_atca_enable(int         val) { mgos_config_set_sys_atca_enable(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_sys_atca_i2c_addr(int         val) { mgos_config_set_sys_atca_i2c_addr(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_sys_atca_ecdh_slots_mask(int         val) { mgos_config_set_sys_atca_ecdh_slots_mask(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_conf_acl(const char *val) { mgos_config_set_conf_acl(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_i2c_enable(int         val) { mgos_config_set_i2c_enable(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_i2c_freq(int         val) { mgos_config_set_i2c_freq(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_i2c_debug(int         val) { mgos_config_set_i2c_debug(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_i2c_unit_no(int         val) { mgos_config_set_i2c_unit_no(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_i2c_sda_gpio(int         val) { mgos_config_set_i2c_sda_gpio(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_i2c_scl_gpio(int         val) { mgos_config_set_i2c_scl_gpio(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_rpc_enable(int         val) { mgos_config_set_rpc_enable(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_rpc_max_frame_size(int         val) { mgos_config_set_rpc_max_frame_size(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_rpc_max_queue_length(int         val) { mgos_config_set_rpc_max_queue_length(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_rpc_default_out_channel_idle_close_timeout(int         val) { mgos_config_set_rpc_default_out_channel_idle_close_timeout(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_rpc_acl_file(const char *val) { mgos_config_set_rpc_acl_file(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_rpc_auth_domain(const char *val) { mgos_config_set_rpc_auth_domain(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_rpc_auth_file(const char *val) { mgos_config_set_rpc_auth_file(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_rpc_uart_uart_no(int         val) { mgos_config_set_rpc_uart_uart_no(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_rpc_uart_baud_rate(int         val) { mgos_config_set_rpc_uart_baud_rate(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_rpc_uart_fc_type(int         val) { mgos_config_set_rpc_uart_fc_type(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_ap_enable(int         val) { mgos_config_set_wifi_ap_enable(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_ap_ssid(const char *val) { mgos_config_set_wifi_ap_ssid(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_ap_pass(const char *val) { mgos_config_set_wifi_ap_pass(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_ap_hidden(int         val) { mgos_config_set_wifi_ap_hidden(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_ap_channel(int         val) { mgos_config_set_wifi_ap_channel(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_ap_max_connections(int         val) { mgos_config_set_wifi_ap_max_connections(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_ap_ip(const char *val) { mgos_config_set_wifi_ap_ip(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_ap_netmask(const char *val) { mgos_config_set_wifi_ap_netmask(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_ap_gw(const char *val) { mgos_config_set_wifi_ap_gw(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_ap_dhcp_start(const char *val) { mgos_config_set_wifi_ap_dhcp_start(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_ap_dhcp_end(const char *val) { mgos_config_set_wifi_ap_dhcp_end(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_ap_trigger_on_gpio(int         val) { mgos_config_set_wifi_ap_trigger_on_gpio(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_ap_disable_after(int         val) { mgos_config_set_wifi_ap_disable_after(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_ap_hostname(const char *val) { mgos_config_set_wifi_ap_hostname(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_ap_keep_enabled(int         val) { mgos_config_set_wifi_ap_keep_enabled(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta_enable(int         val) { mgos_config_set_wifi_sta_enable(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta_ssid(const char *val) { mgos_config_set_wifi_sta_ssid(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta_pass(const char *val) { mgos_config_set_wifi_sta_pass(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta_user(const char *val) { mgos_config_set_wifi_sta_user(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta_anon_identity(const char *val) { mgos_config_set_wifi_sta_anon_identity(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta_cert(const char *val) { mgos_config_set_wifi_sta_cert(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta_key(const char *val) { mgos_config_set_wifi_sta_key(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta_ca_cert(const char *val) { mgos_config_set_wifi_sta_ca_cert(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta_ip(const char *val) { mgos_config_set_wifi_sta_ip(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta_netmask(const char *val) { mgos_config_set_wifi_sta_netmask(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta_gw(const char *val) { mgos_config_set_wifi_sta_gw(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta_nameserver(const char *val) { mgos_config_set_wifi_sta_nameserver(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta_dhcp_hostname(const char *val) { mgos_config_set_wifi_sta_dhcp_hostname(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta1_enable(int         val) { mgos_config_set_wifi_sta1_enable(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta1_ssid(const char *val) { mgos_config_set_wifi_sta1_ssid(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta1_pass(const char *val) { mgos_config_set_wifi_sta1_pass(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta1_user(const char *val) { mgos_config_set_wifi_sta1_user(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta1_anon_identity(const char *val) { mgos_config_set_wifi_sta1_anon_identity(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta1_cert(const char *val) { mgos_config_set_wifi_sta1_cert(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta1_key(const char *val) { mgos_config_set_wifi_sta1_key(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta1_ca_cert(const char *val) { mgos_config_set_wifi_sta1_ca_cert(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta1_ip(const char *val) { mgos_config_set_wifi_sta1_ip(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta1_netmask(const char *val) { mgos_config_set_wifi_sta1_netmask(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta1_gw(const char *val) { mgos_config_set_wifi_sta1_gw(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta1_nameserver(const char *val) { mgos_config_set_wifi_sta1_nameserver(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta1_dhcp_hostname(const char *val) { mgos_config_set_wifi_sta1_dhcp_hostname(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta2_enable(int         val) { mgos_config_set_wifi_sta2_enable(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta2_ssid(const char *val) { mgos_config_set_wifi_sta2_ssid(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta2_pass(const char *val) { mgos_config_set_wifi_sta2_pass(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta2_user(const char *val) { mgos_config_set_wifi_sta2_user(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta2_anon_identity(const char *val) { mgos_config_set_wifi_sta2_anon_identity(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta2_cert(const char *val) { mgos_config_set_wifi_sta2_cert(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta2_key(const char *val) { mgos_config_set_wifi_sta2_key(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta2_ca_cert(const char *val) { mgos_config_set_wifi_sta2_ca_cert(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta2_ip(const char *val) { mgos_config_set_wifi_sta2_ip(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta2_netmask(const char *val) { mgos_config_set_wifi_sta2_netmask(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta2_gw(const char *val) { mgos_config_set_wifi_sta2_gw(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta2_nameserver(const char *val) { mgos_config_set_wifi_sta2_nameserver(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta2_dhcp_hostname(const char *val) { mgos_config_set_wifi_sta2_dhcp_hostname(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta_cfg_idx(int         val) { mgos_config_set_wifi_sta_cfg_idx(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_wifi_sta_connect_timeout(int         val) { mgos_config_set_wifi_sta_connect_timeout(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_board_led1_pin(int         val) { mgos_config_set_board_led1_pin(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_board_led1_active_high(int         val) { mgos_config_set_board_led1_active_high(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_board_led2_pin(int         val) { mgos_config_set_board_led2_pin(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_board_led2_active_high(int         val) { mgos_config_set_board_led2_active_high(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_board_led3_pin(int         val) { mgos_config_set_board_led3_pin(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_board_led3_active_high(int         val) { mgos_config_set_board_led3_active_high(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_board_btn1_pin(int         val) { mgos_config_set_board_btn1_pin(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_board_btn1_pull_up(int         val) { mgos_config_set_board_btn1_pull_up(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_board_btn2_pin(int         val) { mgos_config_set_board_btn2_pin(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_board_btn2_pull_up(int         val) { mgos_config_set_board_btn2_pull_up(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_board_btn3_pin(int         val) { mgos_config_set_board_btn3_pin(&mgos_sys_config, val); }
static inline void mgos_sys_config_set_board_btn3_pull_up(int         val) { mgos_config_set_board_btn3_pull_up(&mgos_sys_config, val); }


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MGOS_CONFIG_H_ */
