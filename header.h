#ifndef HEADER_H
#define HEADER_H

#include "types.h"

typedef struct _MP3
{
    /* To View the File  */
    char *src_file_fname;
    FILE *fptr_src_file;
    char frame_Id[4];

    char ID3_Tag[3];
    int Version_Tag[3];
    char Tag[3];
    uint size_count;

    

    char *TAG_Name;
    uint TAG_Name_size;

    char *Artist_name;
    uint Artist_name_size;

    char *Title;
    uint Title_size;

    char *Album;
    uint Album_size;

    char *Year;
    uint Year_size;

    char *Content;
    uint Content_size;

    char *Comment;
    uint Comment_size;

    char *frame;

    /* To edit The File*/

    /* Source MP3 file Info */
    FILE *fptr_src_edit_file;

    /* Updated value Info passed in the Command Line */
    char frame_Id_edit[5];
    char frame_Id_value[100];
    uint frame_Id_size;

} Music;

OperationType check_operation_type(char *argv[]);

/* Functions related to view details of the File*/


Status read_and_validate_args(char **argv, Music *MP3);

Status open_files(int argc, char **argv, Music *MP3);

Status Check_ID3_Tag(Music *MP3);

Status Check_Version_Tag(Music *MP3);

Status Check_Extension(char **argv, Music *MP3);

Status view(Music *MP3);

Status Check_Tag(Music *MP3);

Status get_and_display_data(const char *frame_descriptions, const char *frame_ids, char *frame_Id, char **tag,  uint *tag_size, Music *MP3);

/* Functions related to edit details of the File*/

Status edit_read_and_validate_args(char **argv, Music *MP3);

Status edit_open_files(int argc, char **argv, Music *MP3);

Status edit_Check_ID3_Tag(Music *MP3);

Status edit_Check_Version_Tag(Music *MP3);

Status edit_Check_Extension(char **argv, Music *MP3);

Status edit(Music *MP3);

Status edit_Check_Tag(Music *MP3);

Status edit_get_and_display_data(const char *frame_descriptions, const char *frame_ids, char *frame_Id, char **tag,  uint *tag_size, Music *MP3);
#endif