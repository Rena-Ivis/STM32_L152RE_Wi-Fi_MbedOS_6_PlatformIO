#include "mbed.h"
#include "TCPSocket.h"
#include "SpwfSAInterface.h"

SpwfSAInterface stmWifi;
/* WiFi Example
 * Copyright (c) 2016 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

WiFiInterface *wifi;

const char *sec2str(nsapi_security_t sec) {
    switch (sec)
    {
    case NSAPI_SECURITY_NONE:
        return "None";
    case NSAPI_SECURITY_WEP:
        return "WEP";
    case NSAPI_SECURITY_WPA:
        return "WPA";
    case NSAPI_SECURITY_WPA2:
        return "WPA2";
    case NSAPI_SECURITY_WPA_WPA2:
        return "WPA/WPA2";
    case NSAPI_SECURITY_UNKNOWN:
    default:
        return "Unknown";
    }
}

int scan_demo(WiFiInterface *wifi) {
    WiFiAccessPoint *ap;

    printf("Scan:\n");
    int count = 30;

    ap = new WiFiAccessPoint[count];
    count = wifi->scan(ap, count);

    if (count <= 0)
    {
        printf("scan() failed with return value: %d\n", count);
        return 0;
    }

    for (int i = 0; i < count; i++)
    {
        printf("Network: %s secured: %s BSSID: %hhX:%hhX:%hhX:%hhx:%hhx:%hhx RSSI: %hhd Ch: %hhd\n", ap[i].get_ssid(),
               sec2str(ap[i].get_security()), ap[i].get_bssid()[0], ap[i].get_bssid()[1], ap[i].get_bssid()[2],
               ap[i].get_bssid()[3], ap[i].get_bssid()[4], ap[i].get_bssid()[5], ap[i].get_rssi(), ap[i].get_channel());
    }
    printf("%d networks available.\n", count);

    delete[] ap;
    return count;
}

int main() {
    SocketAddress sa;
    int count = 0;

    printf("WiFi example\n");

    wifi = &stmWifi;
    if (!wifi) {
        printf("ERROR: No WiFiInterface found.\n");
        return -1;
    }

    count = scan_demo(wifi);
    if (count == 0) {
        printf("No WIFI APNs found - can't continue further.\n");
        return -1;
    }

    printf("\nConnecting to %s...\n", MBED_CONF_APP_WIFI_SSID);
    int ret = wifi->connect(MBED_CONF_APP_WIFI_SSID, MBED_CONF_APP_WIFI_PASSWORD, NSAPI_SECURITY_WPA_WPA2);
    if (ret != 0) {
        printf("\nConnection error: %d\n", ret);
        return -1;
    }

    printf("Success\n\n");
    printf("MAC: %s\n", wifi->get_mac_address());
    wifi->get_ip_address(&sa);
    printf("IP: %s\r\n", sa.get_ip_address());
    wifi->get_netmask(&sa);
    printf("Netmask: %s\r\n", sa.get_ip_address());
    wifi->get_gateway(&sa);
    printf("Gateway: %s\r\n", sa.get_ip_address());
    printf("RSSI: %d\n\n", wifi->get_rssi());

    wifi->disconnect();

    printf("\nDone\n");
}