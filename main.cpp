#include <iostream>
#include "header.h"
#include "types.h"
#include <cstring>
using namespace std;

Music MP3;
int main(int argc, char **argv)
{
    if(check_operation_type(argv) == e_view)
    {
        cout << "Viewing option selected" << endl;
        if (read_and_validate_args(argv, &MP3) == e_success)
        {
            cout << "Successfully read and validated the arguements" << endl;
            if (open_files(argc, argv, &MP3) == e_success)
            {
                cout << "Successfully opened the files" << endl;
                if(Check_ID3_Tag(&MP3) == e_success)
                {
                    cout << "Successfully checked the ID3 Tag" << endl;
                    if (Check_Version_Tag(&MP3) == e_success)
                    {
                        cout << "Successfully checked the version tag" << endl;
                        if (Check_Extension(argv, &MP3) == e_success)
                        {
                            cout << "Successfully checked the extension" << endl;
                            if (view(&MP3) == e_success)
                            {
                                cout << "Successfully viewed the details of MP3 file" << endl;
                            }
                            else
                            {
                                cout << "Viewing Function Failed" << endl;
                            }
                        }
                        else
                        {
                            cout << "Failed to check the extension" << endl;
                        } 
                    }
                    else
                    {
                        cout << "Failed to check the version tag" << endl;
                    }
                }
                else
                {
                    cout << "Failed to check the ID3 Tag" << endl;
                }
            }
            else
            {
                cout << "Failed to open the files" << endl;
            }
        }
        else
        {
            cout << "Failed to read and validate the arguemnets" << endl;
        }
    }

    if (check_operation_type(argv) == e_edit)
    {
        cout << "Edit option selected" << endl;
        if (edit_read_and_validate_args(argv, &MP3) == e_success)
        {
            cout << "Successfully read and validated the arguements" << endl;
            if (edit_open_files(argc, argv, &MP3) == e_success)
            {
                cout << "Successfully opened the files" << endl;
                if(edit_Check_ID3_Tag(&MP3) == e_success)
                {
                    cout << "Successfully checked the ID3 Tag" << endl;
                    if (edit_Check_Version_Tag(&MP3) == e_success)
                    {
                        cout << "Successfully checked the version tag" << endl;
                        if (edit_Check_Extension(argv, &MP3) == e_success)
                        {
                            cout << "Successfully checked the extension" << endl;
                            if (edit(&MP3) == e_success)
                            {
                                cout << "Successfully edited the details of MP3 file" << endl;
                            }
                            else
                            {
                                cout << "Editing Function Failed" << endl;
                            }
                        }
                        else
                        {
                            cout << "Failed to check the extension" << endl;
                        } 
                    }
                    else
                    {
                        cout << "Failed to check the version tag" << endl;
                    }
                }
                else
                {
                    cout << "Failed to check the ID3 Tag" << endl;
                }
            }
            else
            {
                cout << "Failed to open the files" << endl;
            }
        }
        else
        {
            cout << "Failed to read and validate the arguemnets" << endl;
        }
    }

    if (check_operation_type(argv) == e_help)
    {
        cout << "-------------Usage------------" << endl;
        cout << "1.  -v - View the list of all items" << endl;
        cout << "2.  -e - Edit the list of all items" << endl;
        cout << "2.1 -t - Edit the Song Titlg" << endl;
        cout << "2.2 -a - Edit the Artist Name" << endl;
        cout << "2.3 -A - Edit the Album Name" << endl;
        cout << "2.4 -y - Edit the Year of song released" << endl;
        cout << "2.5 -m - Edit the Content of the song" << endl;
        cout << "2.6 -c - Edit the Comments for the song" << endl;
    }
}

OperationType check_operation_type(char **argv)
{
    if (strcmp(argv[1], "-v") == 0)
    {
        return e_view;
    }
    else if (strcmp(argv[1], "-e") == 0)
    {
        return e_edit;
    }
    else
    {
        return e_help;
    }
}

