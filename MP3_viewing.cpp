#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "header.h"
#include <iomanip>
using namespace std;

Status read_and_validate_args(char **argv, Music *MP3)
{
    if (strcmp(strstr(argv[2], "."), ".mp3") == 0)
    {
        MP3->src_file_fname = argv[2];
    }
    else
    {
        return e_failure;
    }
    return e_success;
}

Status open_files(int argc, char **argv, Music *MP3)
{
    if (argc >= 2)
    {
        MP3->fptr_src_file = fopen(argv[2], "r");
    }
    if (MP3->fptr_src_file == NULL)
    {
        cout << "Failed to open the file " << endl;
        return e_failure;
    }
    return e_success;
}

Status Check_ID3_Tag(Music *MP3)
{
    fread(MP3->ID3_Tag, 3, sizeof(char), MP3->fptr_src_file);
    if (MP3->ID3_Tag[0] == 'I' && MP3->ID3_Tag[1] == 'D' && MP3->ID3_Tag[2] == '3')
    {
        cout << "ID3 Tag is " << MP3->ID3_Tag << endl;
    }
    else
    {
        return e_failure;
    }
    return e_success;
}

Status Check_Version_Tag(Music *MP3)
{
    fseek(MP3->fptr_src_file, 3, SEEK_SET);
    fread(MP3->Version_Tag, 3, sizeof(char), MP3->fptr_src_file);
    if (MP3->Version_Tag[0] == 0x03 && MP3->Version_Tag[1] == 0x00 && MP3->Version_Tag[2] == 0x00)
    {
        cout << "The version Tag is " << MP3->Version_Tag[0] << MP3->Version_Tag[1] << MP3->Version_Tag[2] << endl;
    }
    else
    {
        return e_failure;
    }
    return e_success;
}

Status Check_Extension(char **argv, Music *MP3)
{
    if (strcmp(strstr(argv[2], "."), ".mp3") == 0)
    {
        cout << "The extension is " << strstr(argv[2], ".") << endl;
    }
    else
    {
        return e_failure;
    }
    return e_success;
}

Status get_and_display_data(const char *frame_descriptions[], const char *frame_ids[], char *frame_Id, char **tag, uint *tag_size, Music *MP3)
{
    static int flag = 0;
    if (flag == 0)
    {
        cout << "------------------------------------" << endl;
        cout << setw(30) << "MP3 File Details" << endl;
        cout << "------------------------------------" << endl;
        flag = 1;
    }

    size_t count;
    long current_position = ftell(MP3->fptr_src_file);
    count = fread(frame_Id, 1, 4, MP3->fptr_src_file);
    if (count != 4)
    {
        cout << "Failed to read the frame Id" << endl;
        return e_failure;
    }
    frame_Id[4] = '\0';  // Null-terminate the string
    
    for (int i = 0; frame_ids[i] != NULL; i++)
    {
        if (strcmp(frame_Id, frame_ids[i]) == 0)
        {
            uint size_bytes;
            count = fread(&size_bytes, 1, 4, MP3->fptr_src_file);
            if (count != 4)
            {
                cout << "Failed to read the size" << endl;
                return e_failure;
            }

            // Reverse the bytes to get the correct tag size (big-endian to little-endian)
            *tag_size = ((size_bytes & 0xFF) << 24) |
                        ((size_bytes & 0xFF00) << 8) |
                        ((size_bytes & 0xFF0000) >> 8) |
                        ((size_bytes >> 24) & 0xFF);

            *tag = (char *)malloc((*tag_size + 1) * sizeof(char));
            if (*tag == NULL)
            {
                cout << "Failed to allocate the memory for the tag" << endl;
                return e_failure;
            }

            // Skip the frame flags
            fseek(MP3->fptr_src_file, 3, SEEK_CUR);

            // Read the content
            count = fread(*tag, 1, *tag_size, MP3->fptr_src_file);
            if (count < *tag_size)
            {
                cout << "Failed to read the content" << endl;
                free(*tag);
                *tag = NULL;
                return e_failure;
            }
            (*tag)[*tag_size - 1] = '\0';  // Null-terminate the tag

            cout << frame_descriptions[i] << ": " << *tag << endl;

            long next_frame_position = ftell(MP3->fptr_src_file);
            fseek(MP3->fptr_src_file, next_frame_position - 1, SEEK_SET);
            break;
        }
    }

    return e_success;
}

Status Check_Tag(Music *MP3)
{
    fseek(MP3->fptr_src_file, 0, SEEK_SET);
    fseek(MP3->fptr_src_file, 10, SEEK_SET);
    Status ret;

    const char* frame_descriptions[] = {"TITLE", "ARTIST_NAME", "ALBUM_NAME", "YEAR", "CONTENT", "COMMENTS", NULL};
    const char* frame_ids[] = {"TIT2", "TPE1", "TALB", "TYER", "TCON", "COMM", NULL};
    MP3->size_count = sizeof(frame_ids) / sizeof(frame_ids[0]) - 1;
    for (int i = 0; i < MP3->size_count; i++)
    {
        char frame_Id[5] = {0};
        char *tag = NULL;
        uint tag_size = 0;
        ret = get_and_display_data(frame_descriptions, frame_ids, frame_Id, &tag, &tag_size, MP3);
        free(tag);
    }

    cout << "------------------------------------------------" << endl;
    fclose(MP3->fptr_src_file);
    return e_success;
}


Status view(Music *MP3)
{
    if (Check_Tag(MP3) == e_success)
    {
        cout << "Successfully checked the Tag" << endl;
    }
    else
    {
        cout << "Failed to check the Tag" << endl;
        return e_failure;
    }
    return  e_success;
}
