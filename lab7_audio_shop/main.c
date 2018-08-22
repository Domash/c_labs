#include <mm_malloc.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

const int BUFFER_SIZE = 100;

char buff[BUFFER_SIZE];

typedef struct Singer {
    char *name;
    bool *flag;
    int number_of_albums;
    char **list_of_albums;
    int number_of_tracks;
    char **list_of_tracks;
    char *information_abour_singer;
} Singer;

int get_int() {
    int res;
    while(true) {
        if(scanf("%d", &res) && getchar() == '\n') {
            return res;
        } else {
            printf("Try again\n");
            while(getchar() != '\n') {}
        }
    }
}

bool string_comparison(const char *str_a, const char *str_b) {
    size_t len_a = strlen(str_a);
    size_t len_b = strlen(str_b);
    
    if(len_a != len_b) return false;
    for(int i = 0; i < len_a; ++i) {
        if(str_a[i] != str_b[i]) return false;
    }
    return true;
}

void clear_buff() {
    fflush(stdin);
    fflush(stdout);
}

void read_name(Singer *new_singer) {
    printf("1.Enter singer's name\n");
    clear_buff();
    gets(buff);
    
    size_t len = strlen(buff);
    new_singer->name = (char*)malloc(sizeof(char) * len);
    
    for(int i = 0; i < len; ++i) {
        new_singer -> name[i] = buff[i];
    }
}

void read_albums(Singer *new_singer) {
    clear_buff();
    printf("2.Numer of albums:\n");
    
    int number_of_albums = get_int();
    new_singer -> number_of_albums = number_of_albums;
    new_singer -> list_of_albums = (char**)malloc(sizeof(char*) * number_of_albums);
    
    for(int i = 0; i < number_of_albums; ++i) {
        
        gets(buff);
        size_t len = strlen(buff);
        new_singer -> list_of_albums[i] = (char*)malloc(sizeof(char) * len);
        
        for(int j = 0; j < len; ++j) {
            new_singer -> list_of_albums[i][j] = buff[j];
        }
    }
}

void read_tracks(Singer *new_singer) {
    clear_buff();
    printf("3.Numer of tracks:\n");
    
    int number_of_tracks = get_int();
    new_singer -> flag = (bool*)malloc(sizeof(bool) * number_of_tracks);
    
    for(int i = 0; i < number_of_tracks; ++i) {
        new_singer -> flag[i] = false;
    }
    
    new_singer -> number_of_tracks = number_of_tracks;
    new_singer -> list_of_tracks = (char**)malloc(sizeof(char*) * number_of_tracks);
    
    for(int i = 0; i < number_of_tracks; ++i) {
        gets(buff);
        size_t len = strlen(buff);
        new_singer -> list_of_tracks[i] = (char*)malloc(sizeof(char) * len);
        for(int j = 0; j < len; ++j) {
            new_singer -> list_of_tracks[i][j] = buff[j];
        }
    }
}

void read_information(Singer *new_singer) {
    clear_buff();
    printf("Info");
    gets(buff);
    
    size_t len = strlen(buff);
    new_singer -> information_abour_singer = (char*)malloc(sizeof(char) * len);
    
    for(int i = 0; i < len; ++i) {
        new_singer -> information_abour_singer[i] = buff[i];
    }
}

void print_information(Singer *singer) {
    printf("\nArtist: %s\n", singer -> name);
    printf("Info about artist: %s\n", singer -> information_abour_singer);
    printf("Number of albums = %d\n", singer -> number_of_albums);
    
    for(int i = 0; i < singer -> number_of_albums; ++i) {
        printf("   %d.%s\n", i + 1, singer -> list_of_albums[i]);
    }
    
    printf("Number of tracks = %d\n", singer -> number_of_tracks);
    
    for(int i = 0; i < singer -> number_of_tracks; ++i) {
        printf("   %d.%s\n", i + 1, singer -> list_of_tracks[i]);
    }
    
    printf("\n");
}

void search_singer_by_name(int *size_of_list_of_singers, Singer ***list_of_singers) {
    clear_buff();
    printf("Enter singer's name\n");
    
    gets(buff);
    size_t len = strlen(buff);
    char *name = (char*)malloc(sizeof(char) * len);
    
    for(int i = 0; i < len; ++i) {
        name[i] = buff[i];
    }
    
    for(int i = 0; i < *size_of_list_of_singers; ++i) {
        if(string_comparison(name, (*list_of_singers[i]) -> name) == true) {
            print_information(*list_of_singers[i]);
            return;
        }
    }
    
    printf("Information is absent\n\n");
}

void search_singer_by_track(int *size_of_list_of_singers, Singer ***list_of_singers) {
    clear_buff();
    printf("Enter track\n");
    
    gets(buff);
    size_t len = strlen(buff);
    char *name_of_track = (char*)malloc(sizeof(char) * len);
    
    for(int i = 0; i < len; ++i) {
        name_of_track[i] = buff[i];
    }
    
    for(int i = 0; i < *size_of_list_of_singers; ++i) {
        for(int j = 0; j < (*list_of_singers[i]) -> number_of_tracks; ++j) {
            if(string_comparison(name_of_track, (*list_of_singers[i]) -> list_of_tracks[j]) == true
               && (*list_of_singers[i]) -> flag[j] == false) {
                print_information(*list_of_singers[i]);
                return;
            }
        }
    }

    printf("Information is absent\n\n");
}

void search_singer_by_album(int *size_of_list_of_singers, Singer ***list_of_singers) {
    clear_buff();
    printf("Enter album\n");
    
    gets(buff);
    size_t len = strlen(buff);
    char *name_of_album = (char*)malloc(sizeof(char) * len);
    
    for(int i = 0; i < len; ++i) {
        name_of_album[i] = buff[i];
    }
    
    for(int i = 0; i < *size_of_list_of_singers; ++i) {
        for(int j = 0; j < (*list_of_singers[i]) -> number_of_albums; ++j) {
            if(string_comparison(name_of_album, (*list_of_singers[i]) -> list_of_albums[j]) == true) {
                print_information(*list_of_singers[i]);
                return;
            }
        }
    }

    printf("Information is absent\n\n");
}

void add_singer(int *size_of_list_of_singers, Singer ***list_of_singers) {
    Singer *new_singer = (Singer*)malloc(sizeof(Singer));
    *list_of_singers = (Singer**)realloc(*list_of_singers, (*size_of_list_of_singers + 1) * sizeof(Singer*));
    
    read_name(new_singer);
    read_albums(new_singer);
    read_tracks(new_singer);
    read_information(new_singer);
    
    *list_of_singers[*size_of_list_of_singers] = new_singer;
    *size_of_list_of_singers = *size_of_list_of_singers + 1;
}

void move_track_in_basket(int *size_of_list_of_singers, Singer ***list_of_singers) {
    clear_buff();
    printf("Enter track\n");

    gets(buff);
    size_t len = strlen(buff);
    char *name_of_track = (char*)malloc(sizeof(char) * len);
    
    for(int i = 0; i < len; ++i) {
        name_of_track[i] = buff[i];
    }

    for(int i = 0; i < *size_of_list_of_singers; ++i) {
        for(int j = 0; j < (*list_of_singers[i]) -> number_of_tracks; ++j) {
            if(string_comparison(name_of_track, (*list_of_singers[i]) -> list_of_tracks[j]) == true) {
                (*list_of_singers[i]) -> flag[j] = 1;
            }
        }
    }

    printf("\n");
}

void restore_track_from_basket(int *size_of_list_of_singers, Singer ***list_of_singers) {
    clear_buff();
    printf("Enter track\n");
    
    gets(buff);
    size_t len = strlen(buff);
    char *name_of_track = (char*)malloc(sizeof(char) * len);
    
    for(int i = 0; i < len; ++i) {
        name_of_track[i] = buff[i];
    }

    for(int i = 0; i < *size_of_list_of_singers; ++i) {
        for(int j = 0; j < (*list_of_singers[i]) -> number_of_tracks; ++j) {
            if(string_comparison(name_of_track, (*list_of_singers[i]) -> list_of_tracks[j]) == true) {
                (*list_of_singers[i]) -> flag[j] = 0;
            }
        }
    }
    printf("\n");
}

void get_report(int *size_of_list_of_singers, Singer ***list_of_singers) {
    printf("\nCurrent status:\n");
    printf("   Number of artist: %d\n", *size_of_list_of_singers);

    int all_tracks = 0, all_albums = 0;
    for(int i = 0; i < *size_of_list_of_singers; ++i) {
        all_tracks += (*list_of_singers[i]) -> number_of_tracks;
        all_albums += (*list_of_singers[i]) -> number_of_albums;
    }

    printf("   Number of albums: %d\n", all_albums);
    printf("   Number of tracks: %d\n\n", all_tracks);
}

void print_commands() {
    printf("1.Add singer\n");
    printf("2.Find singer by name\n");
    printf("3.Find singer by track\n");
    printf("4.Find singer by album\n");
    printf("5.Output of the store report\n");
    printf("6.Move track in basket\n");
    printf("7.Restore track from basket\n");
    printf("8.EXIT\n\n");
}

void menu(int *size_of_list_of_singers, Singer ***list_of_singers) {
    bool ok = true;
    while(ok) {
        
        print_commands();
        int command = get_int();
        
        switch(command) {
            case 1:
                add_singer(size_of_list_of_singers, list_of_singers);
                break;
            case 2:
                search_singer_by_name(size_of_list_of_singers, list_of_singers);
                break;
            case 3:
                search_singer_by_track(size_of_list_of_singers, list_of_singers);
                break;
            case 4:
                search_singer_by_album(size_of_list_of_singers, list_of_singers);
                break;
            case 5:
                get_report(size_of_list_of_singers, list_of_singers);
                break;
            case 6:
                move_track_in_basket(size_of_list_of_singers, list_of_singers);
                break;
            case 7:
                restore_track_from_basket(size_of_list_of_singers, list_of_singers);
                break;
            case 8:
                return;
                break;
            default:
                printf("Invalid command, try again\n\n");
                break;
        }
    }
}

void clear_memory(int *size_of_list_of_singers, Singer ***list_of_singers) {
    for(int i = 0; i < *size_of_list_of_singers; ++i) {
        
        for(int j = 0; j < (*list_of_singers[i]) -> number_of_albums; ++j) {
            free((*list_of_singers[i]) -> list_of_albums[j]);
        }

        for(int j = 0; j < (*list_of_singers[i]) -> number_of_tracks; ++j) {
            free((*list_of_singers[i]) -> list_of_tracks[j]);
        }

        free((*list_of_singers[i]) -> information_abour_singer);
        free((*list_of_singers[i]) -> flag);
        free(*list_of_singers[i]);
    
    }
    
    free(*list_of_singers);
}

int main() {

    Singer **list_of_singers = NULL;
    int size_of_list_of_singers = 0;
    menu(&size_of_list_of_singers, &list_of_singers);
    clear_memory(&size_of_list_of_singers, &list_of_singers);
    
    return 0;
}

