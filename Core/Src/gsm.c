/*
 * gsm.c
 *
 *  Created on: May 13, 2025
 *      Author: Admin
 */
#include "main.h"
#include "sys_init.h"


//const char ca_cert[] =
//"-----BEGIN CERTIFICATE-----\r\n"
//"MIIFFjCCAv6gAwIBAgIRAJErCErPDBinU/bWLiWnX1owDQYJKoZIhvcNAQELBQAw\r\n"
//"TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh\r\n"
//"cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMjAwOTA0MDAwMDAw\r\n"
//"WhcNMjUwOTE1MTYwMDAwWjAyMQswCQYDVQQGEwJVUzEWMBQGA1UEChMNTGV0J3Mg\r\n"
//"RW5jcnlwdDELMAkGA1UEAxMCUjMwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEK\r\n"
//"AoIBAQC7AhUozPaglNMPEuyNVZLD+ILxmaZ6QoinXSaqtSu5xUyxr45r+XXIo9cP\r\n"
//"R5QUVTVXjJ6oojkZ9YI8QqlObvU7wy7bjcCwXPNZOOftz2nwWgsbvsCUJCWH+jdx\r\n"
//"sxPnHKzhm+/b5DtFUkWWqcFTzjTIUu61ru2P3mBw4qVUq7ZtDpelQDRrK9O8Zutm\r\n"
//"NHz6a4uPVymZ+DAXXbpyb/uBxa3Shlg9F8fnCbvxK/eG3MHacV3URuPMrSXBiLxg\r\n"
//"Z3Vms/EY96Jc5lP/Ooi2R6X/ExjqmAl3P51T+c8B5fWmcBcUr2Ok/5mzk53cU6cG\r\n"
//"/kiFHaFpriV1uxPMUgP17VGhi9sVAgMBAAGjggEIMIIBBDAOBgNVHQ8BAf8EBAMC\r\n"
//"AYYwHQYDVR0lBBYwFAYIKwYBBQUHAwIGCCsGAQUFBwMBMBIGA1UdEwEB/wQIMAYB\r\n"
//"Af8CAQAwHQYDVR0OBBYEFBQusxe3WFbLrlAJQOYfr52LFMLGMB8GA1UdIwQYMBaA\r\n"
//"FHm0WeZ7tuXkAXOACIjIGlj26ZtuMDIGCCsGAQUFBwEBBCYwJDAiBggrBgEFBQcw\r\n"
//"AoYWaHR0cDovL3gxLmkubGVuY3Iub3JnLzAnBgNVHR8EIDAeMBygGqAYhhZodHRw\r\n"
//"Oi8veDEuYy5sZW5jci5vcmcvMCIGA1UdIAQbMBkwCAYGZ4EMAQIBMA0GCysGAQQB\r\n"
//"gt8TAQEBMA0GCSqGSIb3DQEBCwUAA4ICAQCFyk5HPqP3hUSFvNVneLKYY611TR6W\r\n"
//"PTNlclQtgaDqw+34IL9fzLdwALduO/ZelN7kIJ+m74uyA+eitRY8kc607TkC53wl\r\n"
//"ikfmZW4/RvTZ8M6UK+5UzhK8jCdLuMGYL6KvzXGRSgi3yLgjewQtCPkIVz6D2QQz\r\n"
//"CkcheAmCJ8MqyJu5zlzyZMjAvnnAT45tRAxekrsu94sQ4egdRCnbWSDtY7kh+BIm\r\n"
//"lJNXoB1lBMEKIq4QDUOXoRgffuDghje1WrG9ML+Hbisq/yFOGwXD9RiX8F6sw6W4\r\n"
//"avAuvDszue5L3sz85K+EC4Y/wFVDNvZo4TYXao6Z0f+lQKc0t8DQYzk1OXVu8rp2\r\n"
//"yJMC6alLbBfODALZvYH7n7do1AZls4I9d1P4jnkDrQoxB3UqQ9hVl3LEKQ73xF1O\r\n"
//"yK5GhDDX8oVfGKF5u+decIsH4YaTw7mP3GFxJSqv3+0lUFJoi5Lc5da149p90Ids\r\n"
//"hCExroL1+7mryIkXPeFM5TgO9r0rvZaBFOvV2z0gp35Z0+L4WPlbuEjN/lxPFin+\r\n"
//"HlUjr8gRsI3qfJOQFy/9rKIJR0Y/8Omwt/8oTWgy1mdeHmmjk7j1nYsvC9JSQ6Zv\r\n"
//"MldlTTKB3zhThV1+XWYp6rjd5JW1zbVWEkLNxE7GJThEUG3szgBVGP7pSWTUTsqX\r\n"
//"nLRbwHOoq7hHwg==\r\n"
//"-----END CERTIFICATE-----\r\n";
//
//const uint16_t cert_size = strlen(ca_cert);

const char ca_cert[] =
"-----BEGIN CERTIFICATE-----\r\n"
"MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\r\n"
"ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\r\n"
"b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\r\n"
"MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\r\n"
"b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\r\n"
"ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\r\n"
"9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\r\n"
"IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\r\n"
"VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\r\n"
"93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\r\n"
"jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\r\n"
"AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\r\n"
"A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\r\n"
"U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\r\n"
"N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\r\n"
"o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\r\n"
"5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\r\n"
"rqXRfboQnoZsG4q5WTP468SQvvG5\r\n"
"-----END CERTIFICATE-----\r\n";

const uint16_t cert_size = strlen(ca_cert);

const char private_key[] =
"-----BEGIN RSA PRIVATE KEY-----\r\n"
"MIIEowIBAAKCAQEAsJbeGe6NZizwnL5ICEtaVQwH4sfSjTTAPZJ3MCkusivPBzj2\r\n"
"eD1FFuLi2O4ZH7qsTwABtO+CfSHjpWPpvYOUrn+ZwJ9son5UFWo9H2Iycin+SB1O\r\n"
"+NG6cfQ2p6fIR3o61HNGMdvHXU+lp15EZonr/B+w8DCqoZpBOTD7r2WKgF0/eFiQ\r\n"
"2gcHmxImx2WsXFW+kuOS3/BW3nXs9gp0QTbVnrVgseFiTylEncHKp1xsn93aROgO\r\n"
"u0V+1H5aKSAlK3/zQhS6usVC2wuc/Vyo0V8xIqt46H8w8HQCqdjJ2jF+QQ5rEii3\r\n"
"kCWO4HbrRIIV/4rblcBCl+jG/ZDkGprFhHEhWwIDAQABAoIBAEjOKsvuOoYByUIW\r\n"
"gYRJ7PhbeXTahciKEyhPlqxYjlQPE9AagCOavz1sVbKyl9EpGZmImyuKA/arXjv2\r\n"
"MYxdD5PSMAXmtNdZ1jjuED08Myg2gAwjaUfU0FXjJhWBa2Vs04x76ljsEAo8qEOU\r\n"
"7gaInq7YMg8VQYRXIMT/mQT7jFrXZ2/QMpTGhUkI9wCWZBHUvbpvG2XANZCsQsSS\r\n"
"sQTtpP2OWZP7qdN8AeeZ/PcK7JS2sqDf8P/0Ih96874F3CqqOtSm1tteycLqSUtL\r\n"
"+hoXQ7DctEBAaW+g4bStbjKFvUCi+KG/zMT7LVuFVzePIWHhfLYSvi3rwL28EllR\r\n"
"EzyBkUECgYEA4/vwX5i/GNNb59orL9aDiCD4h4Na4nAUIRgInWYxGjyACnoZkU7x\r\n"
"6fvY8md1VcALTabqsLQW9dxiweS3g22ln5tIZE3wojTd4XNyko+s/UduoaxHpF4l\r\n"
"l8GmTGC9w4WJcm1bYZwKbyCatKcD5B7F6mOXe66XIXmIzFJ22r70TnMCgYEAxkoe\r\n"
"uULcvPLbMiPwlFILhLY9dHG8CpL5Wux4aBVvhkva2EyTHwpktGDXBwF8aRQDvzb/\r\n"
"NN86CUuCwpcCx48Gupe8pw0CXAmyrR9fGi2sT79+INLkf7lIAA7mLK04nGRGxNSg\r\n"
"BiIdTMjRAe29BUM9F3oYNpcP8cCL+gTR+gd/f3kCgYEAnwIf47z4Q4texXWfu2zF\r\n"
"LlO4o2NVJyt+jpphn84fnynlL+l7HaLPDR/vbxoDdzxLZexuMbJZdT8xzgQEjnES\r\n"
"HCDEu9i0ZZ2zx0Oq/FejEsAYhEBRc22KkK6qmwi6Mb1YYOuu2YRorpsx65+1Egz4\r\n"
"gwLVK5lYpStL4x388ZJPeMsCgYBsIRsj95wbxWtWqlaU6zCwzBgzGZprQb6MoIsA\r\n"
"Z0ALwe2zKf7IXIiR/IUFov/O5UUtzrXYhSpGy1ChAGxZmlsXAYu0pNl2iytOUN8x\r\n"
"jVp7mncTOy2zoLvsnDNUhZlrXxtgVnp1HcFQj+m53YTIC+SSmtf9XN8q+87ZJivC\r\n"
"5rfWMQKBgCzzWDxhjZXVovptFZZm2sI1fCS6KeqeJ1nQkYGbAEB9PWTpXPBocdVq\r\n"
"oFi9aGkthVnsXRReJiPfyrvmYB/Yqk/8OJyj4a/6zknGOlHM7PCQQ+enf1eB9gm3\r\n"
"fVsixTC2e92wfLTRw9JoE2rRo+9btaI9KpYz4AGtIVTm3PnFYDQp\r\n"
"-----END RSA PRIVATE KEY-----\r\n";

const uint16_t private_key_size = strlen(private_key);

const char certificate[] =
"-----BEGIN CERTIFICATE-----\r\n"
"MIIDWTCCAkGgAwIBAgIUakWX7ICUwRBtgaEgA21Ql3gAefcwDQYJKoZIhvcNAQEL\r\n"
"BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\r\n"
"SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI1MDUwOTEyMDYx\r\n"
"MloXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\r\n"
"ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALCW3hnujWYs8Jy+SAhL\r\n"
"WlUMB+LH0o00wD2SdzApLrIrzwc49ng9RRbi4tjuGR+6rE8AAbTvgn0h46Vj6b2D\r\n"
"lK5/mcCfbKJ+VBVqPR9iMnIp/kgdTvjRunH0NqenyEd6OtRzRjHbx11PpadeRGaJ\r\n"
"6/wfsPAwqqGaQTkw+69lioBdP3hYkNoHB5sSJsdlrFxVvpLjkt/wVt517PYKdEE2\r\n"
"1Z61YLHhYk8pRJ3ByqdcbJ/d2kToDrtFftR+WikgJSt/80IUurrFQtsLnP1cqNFf\r\n"
"MSKreOh/MPB0AqnYydoxfkEOaxIot5AljuB260SCFf+K25XAQpfoxv2Q5BqaxYRx\r\n"
"IVsCAwEAAaNgMF4wHwYDVR0jBBgwFoAUpidZVjv1z1WmkH+nhYdstKwstOAwHQYD\r\n"
"VR0OBBYEFIlQXk0oLkVetMORJxtpOEzLDqsCMAwGA1UdEwEB/wQCMAAwDgYDVR0P\r\n"
"AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQBMxLuuEbCl2tFf0sJJbn3++zGP\r\n"
"KimA123ZflVloo4E0QYRVT5pePQqBogfYspI5iBjqwDxczLh0u4RhrVP6RkwSJoH\r\n"
"88bdvbTlBlNYYzzEJQApC4XeJ6u/+ZltyMrsrv9mymll+dQUDA3PPvSoaTRKmYM7\r\n"
"/gvgvMZunl4KanLOHPA2eS/Zr2XJzbMhkh6r0TW+37orReE15Ou+/y370VMgSdLA\r\n"
"xW3J7+Yem0eIgB/SJON07FhmUVc7rjk5ZGmU/fCuGiVMdt9iR68qr5eLB+kF1LXp\r\n"
"jP06d/4sRrWksGTpDXTwdisIZeQCWWaAXYmvDI11iapOvwlvpTv7Tf46kfeW\r\n"
"-----END CERTIFICATE-----\r\n";

const uint16_t certificate_size = strlen(certificate);


void send_at_command(const char *cmd, char *response, int timeout_ms) {
    memset(buffer, 0, sizeof(buffer));  // Clear receive buffer
    memset(response, 0, 512);           // Clear response buffer
    memset(ATcommand, 0, sizeof(ATcommand)); // Clear AT command buffer

    sprintf(ATcommand, "%s", cmd); // Safely copy the command

    HAL_UART_Transmit(&huart1, (uint8_t *)ATcommand, strlen(ATcommand), timeout_ms);
    HAL_UART_Receive(&huart1, buffer, 512, timeout_ms);

    if (strstr((char *)buffer, "OK")) {
        strncpy(response, (char *)buffer, 512);
        response[255] = '\0';

        snprintf(command, sizeof(command), "Response: %s", response);
        HAL_UART_Transmit(&huart2, (uint8_t *)command, strlen(command), 1000);
    } else {
        response[0] = '\0';  // Clear response if "OK" not found
        snprintf(command, sizeof(command), "Response: NO\r\n");
        HAL_UART_Transmit(&huart2, (uint8_t *)command, strlen(command), 1000);
    }

//    HAL_Delay(1000);
}



void mqtt_init(const char *broker, const char *accesstoken, const char *clientid) {


    send_at_command("AT\r\n",response,500);
//    HAL_Delay(2500);// New
    send_at_command("AT+CFUN=1\r\n",response,500);
//    send_at_command("AT+CPIN?\r\n",response,500);
//    send_at_command("AT+CSQ\r\n",response,500);
    send_at_command("AT+CREG=2\r\n",response,500);
    send_at_command("AT+CEREG=2\r\n",response,500);
//     send_at_command("AT+COPS?\r\n",response,1000);
    send_at_command("AT+CGDCONT=1,\"IP\",\"airtelgprs.com\"\r\n",response,500);

    send_at_command("AT+CGACT=1,1\r\n",response,500);
//    send_at_command("AT+CGATT=1\r\n",response,500);
    send_at_command("AT+CNTP=\"asia.pool.ntp.org\",0\r\n",response,500);
    send_at_command("AT+CNTP\r\n",response,500);
    send_at_command("AT+CCLK?\r\n",response,500);
     send_at_command("AT+IPADDR\r\n",response,1000);
    send_at_command("AT+CGATT=1\r\n",response,500);
//    send_at_command("AT+CGPADDR=1\r\n",response,500);
//     send_at_command("AT+CGACT?\r\n",response,1000);
//     send_at_command("AT+CEREG?\r\n",response,1000);
    send_at_command("AT+NETOPEN\r\n",response,500);
//     send_at_command("AT+NETOPEN?\r\n",response,1000);

    /*AT+CCERTDOWN="ca_cert.pem", 1970
AT+CCERTDOWN="client_cert.pem", 1970
AT+CCERTDOWN="client_key.pem", 1970
AT+CCERTDOWN="password.pem", 1970

*Assign config file

AT+CSSLCFG="cacert",0,"ca_cert.pem"
AT+CSSLCFG="clientcert",0,"client_cert.pem"
AT+CSSLCFG="clientkey",0,"client_key.pem"
AT+CSSLCFG="password",0,"password.pem"*/
//    char at_command[100];
//
//    sprintf(at_command, "AT+CCERTDOWN=\"ca_cert.pem\",%d\r\n", cert_size);
//    send_at_command(at_command, response, 1000);
//    if (strchr(response, '>') != NULL) {
//    	send_at_command(ca_cert, response, 1000);
//
//    }
//
//
//    sprintf(at_command, "AT+CCERTDOWN=\"client_cert.pem\",%d\r\n", certificate_size);
//    send_at_command(at_command, response, 1000);
//    if (strchr(response, '>') != NULL) {
//    	send_at_command(certificate, response, 1000);
//    }
//
//
//    sprintf(at_command, "AT+CCERTDOWN=\"client_key.pem\",%d\r\n", private_key_size);
//    send_at_command(at_command, response, 1000);
//    if (strchr(response, '>') != NULL) {
//    	send_at_command(private_key, response, 1000);
//    }
//    send_at_command("AT+CSSLCFG=\"cacert\",0,\"ca_cert.pem\"\r\n",response,1000);
//    send_at_command("AT+CSSLCFG=\"clientcert\",0,\"client_cert.pem\"\r\n",response,1000);
//    send_at_command("AT+CSSLCFG=\"clientkey\",0,\"client_key.pem\"\r\n",response,1000);





     send_at_command("AT+CSSLCFG=\"sslversion\",0,4\r\n",response,1000);
    send_at_command("AT+CSSLCFG=\"authmode\",0,1\r\n",response,500);
    send_at_command("AT+CSSLCFG=\"cacert\",0,\"ca_cert.pem\"\r\n",response,500);
//     send_at_command("AT+CSSLCFG=\"clientcert\",0,\"client_cert.pem\"\r\n",response,1000);
//     send_at_command("AT+CSSLCFG=\"clientkey\",0,\"client_key.pem\"\r\n",response,1000);
//     send_at_command("AT+CSSLCFG=\"password\",0,\"password.pem\"\r\n",response,1000);
    send_at_command("AT+CSSLCFG=\"enableSNI\",0,1\r\n",response,500);

    send_at_command("AT+CMQTTSTART\r\n", response, 500);
    send_at_command("AT+CCHSET=1,1\r\n", response, 500);
    send_at_command("AT+CCHMODE=1\r\n", response, 500);
    send_at_command("AT+CCHSTART\r\n", response, 500);
    send_at_command("AT+CCHADDR\r\n", response, 500);

//     send_at_command("AT+CCHOPEN\r\n", response, 500);
    send_at_command("AT+CCHCFG=\"sendtimeout\",0,60\r\n", response, 500);
    send_at_command("AT+CCHCFG=\"sslctx\",0,1\r\n", response, 500);
//     send_at_command("AT+CCERTMOVE=\"ca_cert.pem\"\r\n", response, 500);
    send_at_command("AT+CMQTTSSLCFG=0,1\r\n", response, 500);
    send_at_command("AT+CSSLCFG=0\r\n",response,500);

    //Set ID
    char mqtt_id[128];
    snprintf(mqtt_id, sizeof(mqtt_id), "AT+CMQTTACCQ=0,\"%s\",1\r\n",accesstoken);
    send_at_command(mqtt_id, response, 500);

    send_at_command("AT+CMQTTCFG=\"checkUTF8\",0,1\r\n",response,1000);
    send_at_command("AT+CMQTTCFG=\"optimeout\",0,60\r\n",response,1000);
//     send_at_command("AT+CMQTTCONNECT?\r\n",response,100);
//     send_at_command("AT+CCERTLIST", response, 1000);
    // send_at_command("AT+CCERTDELE=\"ca_cert.pem\"", response, 1000);

//    for(int i=0;i<3;i++){
    char mqtt_conn[256];
    snprintf(mqtt_conn, sizeof(mqtt_conn), "AT+CMQTTCONNECT=0,\"tcp://%s\",300,1,\"%s\"\r\n",broker, accesstoken);
//    snprintf(mqtt_conn, sizeof(mqtt_conn), "AT+CMQTTCONNECT=0,\"tcp://%s\",300,1,\"%s,\"%s\"\r\n",broker, accesstoken, clientid);
    send_at_command(mqtt_conn, response, 2500);
//    }
//    HAL_Delay(1500);
    // ESP_LOGI("MQTT", "MQTT connection response: %s", response);

}

void mqtt_publish(const char *topic, const char *data) {
    // Set topic
    char mqtt_topic[128];
    int len;
    len=strlen(topic);
    snprintf(mqtt_topic, sizeof(mqtt_topic), "AT+CMQTTTOPIC=0,%d\r\n", len);
    send_at_command(mqtt_topic, response, 1000);
    send_at_command(topic,response,1000);

    // Send payload
    char mqtt_payload[512];
    len=strlen(data);
    snprintf(mqtt_payload, sizeof(mqtt_payload), "AT+CMQTTPAYLOAD=0,%d\r\n", len);
    send_at_command(mqtt_payload, response, 1000);
    send_at_command(data,response,1000);

    // Publish Data
    send_at_command("AT+CMQTTPUB=0,0,60,1\r\n",response,500);

    // send_at_command("AT+CMQTTDISC=0,60\r\n", response, 2000);
    // send_at_command("AT+CMQTTSTOP\r\n",response,1000);

}

void mqtt_subscribe(const char *topic) {
    //Set topic
    char mqtt_topic[128];
    int len;
    len=strlen(topic);
    snprintf(mqtt_topic, sizeof(mqtt_topic), "AT+CMQTTSUBTOPIC=0,%d,0\r\n", len);
    send_at_command(mqtt_topic, response, 1000);
    // send_at_command("AT+CMQTTSUBTOPIC=0,9,0\r\n",response,1000);
    send_at_command(topic,response,1000);

    //Subscribe
    snprintf(mqtt_topic, sizeof(mqtt_topic), "AT+CMQTTSUB=0,%d,0\r\n", len);
//     send_at_command(mqtt_topic, response, 5000);
    send_at_command("AT+CMQTTSUB=0\r\n",response,1000);
     send_at_command(topic,response,1000);

    if (strstr((char *)buffer, "OK")) {
        strncpy(response, (char *)buffer, 512);
        response[255] = '\0';
        process_sensor_data(response);


    }

    // Disconnect
    // len=strlen(topic);
    // snprintf(mqtt_topic, sizeof(mqtt_topic), "AT+CMQTTUNSUBTOPIC=0,%d", len);
    // send_at_command(mqtt_topic, response, 1000);
    // send_at_command(topic,response,1000);

    // Unsubcribe
        // len=strlen(topic);
    // snprintf(mqtt_topic, sizeof(mqtt_topic), "AT+CMQTTUNSUB==0,%d", len);
    // send_at_command(mqtt_topic, response, 1000);
    // send_at_command(topic,response,1000);

    // send_at_command("AT+CMQTTDISC=0,60\r\n", response, 2000);
    // send_at_command("AT+CMQTTSTOP\r\n",response,1000);


}
void gsm_init(){

    // Initialize MQTT
    const char *broker = "thingsboard.cloud:8883";
    const char *accesstoken = "aCWxFWJedGshl1DowCT8";
    const char *clientid = "KP";
//    const char *broker = "61f18205d9d64ad1b29f6e99d0679efc.s1.eu.hivemq.cloud:8883";
//    const char *accesstoken = "demo1";
//    const char *clientid = "Demo1234";

    mqtt_init(broker, accesstoken, clientid);
//    char msg[30];
//    sprintf(msg, "{\"temperature\":%f}", DataM);
//	HAL_UART_Transmit(&huart2,(uint8_t *)msg,strlen(msg),1000);
//  mqtt_publish("v1/devices/me/telemetry", "{\"temperature\": 51, \"humidity\": 03, \"flowRate\": 4, \"energy\": 91, \"volume\": 563, \"totalVolume\": 64}");
//    mqtt_publish("v1/devices/me/telemetry", msg);

    // mqtt_subscribe("v1/devices/me/telemetry");
}

void gsm_set_clock(){

    send_at_command("AT+CNTP=\"asia.pool.ntp.org\",0\r\n",response,500);
    send_at_command("AT+CNTP\r\n",response,500);
    send_at_command("AT+CCLK?\r\n",response,500);
    char AT[600];
    snprintf(AT, sizeof(AT), "Response: %s", response);

    HAL_UART_Transmit(&huart2,(uint8_t *)AT,strlen(AT),1000);
	SetRTCFromCCLK(response);

}
