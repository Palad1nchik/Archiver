#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define BUFFER_SIZE 1024

int main()
{
    char sourcePath[MAX_PATH];
    char destinationPath[MAX_PATH];
    char zipCommand[MAX_PATH + 20];

    printf("Enter the path of the file or folder to be archived: ");
    fgets(sourcePath, sizeof(sourcePath), stdin);
    sourcePath[strcspn(sourcePath, "\n")] = '\0';

    printf("Enter the path and name for the archive file (including .zip extension): ");
    fgets(destinationPath, sizeof(destinationPath), stdin);
    destinationPath[strcspn(destinationPath, "\n")] = '\0';

    snprintf(zipCommand, sizeof(zipCommand), "powershell Compress-Archive -Path \"%s\" -DestinationPath \"%s\"", sourcePath, destinationPath);

    printf("Archiving files...\n");

    FILE* pipe = _popen(zipCommand, "r");
    if (pipe == NULL)
    {
        printf("Failed to execute compression command.\n");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, pipe) != NULL)
    {
        printf("%s", buffer);
    }

    _pclose(pipe);

    printf("Files archived successfully.\n");

    return 0;
}
