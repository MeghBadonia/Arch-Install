#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void greeting() {
    system("clear");
    printf("\n\n\n\n");
    printf(
        "        █████╗ ██████╗  ██████╗██╗  ██╗    ██╗███╗   ██╗███████╗████████╗ █████╗ ██╗     ██╗     \n"
        "       ██╔══██╗██╔══██╗██╔════╝██║  ██║    ██║████╗  ██║██╔════╝╚══██╔══╝██╔══██╗██║     ██║     \n"
        "       ███████║██████╔╝██║     ███████║    ██║██╔██╗ ██║███████╗   ██║   ███████║██║     ██║     \n"
        "       ██╔══██║██╔══██╗██║     ██╔══██║    ██║██║╚██╗██║╚════██║   ██║   ██╔══██║██║     ██║     \n"
        "       ██║  ██║██║  ██║╚██████╗██║  ██║    ██║██║ ╚████║███████║   ██║   ██║  ██║███████╗███████╗\n"
        "       ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝    ╚═╝╚═╝  ╚═══╝╚══════╝   ╚═╝   ╚═╝  ╚═╝╚══════╝╚══════╝\n"
    );
    printf("\n\n\n\n");
}

void timezone() {
    char timezone[64];
    char cmd[128];

    while (1) {
        printf("[ o ]  Enter timezone : ( Asia/Kolkata ) ");
        scanf("%63s", timezone);

        snprintf(cmd, sizeof(cmd), "sudo timedatectl set-timezone %s > /dev/null 2>&1", timezone);

        if (system(cmd) == 0) {
            printf("[ ✓ ]  Timezone set successfully to %s", timezone);
            printf("\n\n");
            break;
        } else {
            printf("[ x ]  Invalid timezone. Please try again.");
            printf("\n\n");
        }
    }
}

// void networking() {
//     char device[17];
//     char network[33];
//     char password[513];
//     char cmd[256];
//
//     if (system("ping -c 1 google.com > /dev/null 2>&1") == 0) {
//         printf("[ ✓ ]  Internet is connected");
//         printf("\n\n");
//         return;
//     } else {
//         printf("[ x ]  Internet not connected");
//         printf("\n\n");
//     }
//
//     system("iwctl device list");
//
//     printf("[ o ]  Enter device name : ( wlan0 ) ");
//     if (fgets(device, sizeof(device), stdin) != NULL) {
//         device[strcspn(device, "\n")] = '\0';
//         if (strlen(device) == 0) strcpy(device, "wlan0");
//     }
//
//     snprintf(cmd, sizeof(cmd), "iwctl station %s scan", device);
//     system(cmd);
//     snprintf(cmd, sizeof(cmd), "iwctl station %s get-networks", device);
//     system(cmd);
//
//     printf("[ o ]  Enter network name or SSID : ( Max 32 digits ) ");
//     if (fgets(network, sizeof(network), stdin) != NULL) {
//         network[strcspn(network, "\n")] = '\0';
//     }
//
//     printf("[ o ]  Enter network password : ");
//     if (fgets(password, sizeof(password), stdin) != NULL) {
//         password[strcspn(password, "\n")] = '\0';
//     }
//
//     snprintf(cmd, sizeof(cmd), "iwctl --passphrase=%s station %s connect \"%s\"", password, device, network);
//     if (system(cmd) == 0) {
//         printf("[ ✓ ]  Connected to '%s'", network);
//         printf("\n\n");
//     } else {
//         printf("[ x ]  Failed to connect to '%s'", network);
//         printf("\n\n");
//     }
// }

void networking() {
    char device[17];
    char network[33];
    char password[65];
    char cmd[256];

    while (1) {
        if (system("ping -c 1 google.com > /dev/null 2>&1") != 0) {
            printf("[ ✓ ]  Internet is connected");
            printf("\n\n");
            break;
        } else {
            printf("[ x ]  Internet not connected");
            printf("\n\n");
        }

        system("iwctl device list");

        printf("[ o ]  Enter device name : ( wlan0 ) ");
        if (fgets(device, sizeof(device), stdin) != NULL) {
            device[strcspn(device, "\n")] = '\0';
            if (strlen(device) == 0) strcpy(device, "wlan0");
        }

        snprintf(cmd, sizeof(cmd), "iwctl station %s scan", device);
        system(cmd);

        snprintf(cmd, sizeof(cmd), "iwctl station %s get-networks", device);
        system(cmd);

        printf("[ o ]  Enter network name or SSID : ( Max 32 digits ) ");
        if (fgets(network, sizeof(network), stdin) != NULL) {
            network[strcspn(network, "\n")] = '\0';
        }

        printf("[ o ]  Enter network password : ");
        if (fgets(password, sizeof(password), stdin) != NULL) {
            password[strcspn(password, "\n")] = '\0';
        }

        snprintf(cmd, sizeof(cmd), "iwctl --passphrase=%s station %s connect \"%s\"", password, device, network);
        if (system(cmd) == 0) {
            printf("[ ✓ ]  Connected to '%s'", network);
            printf("\n\n");
            break;
        } else {
            printf("[ x ]  Failed to connect to '%s'", network);
            printf("\n\n");
            printf("Retrying...\n\n");
        }
    }
}

void partitioning() {

}

int main() {
    greeting();
    networking();
    timezone();
}
