#include "include/point.h"
#include "include/config.h"
#include "include/type.h"

#include <time.h>
#include <stdio.h>
#include <string.h>

long point_for_line(int lines) {

    switch(lines) {
        case 1: return 40; break;
        case 2: return 100; break;
        case 3: return 300; break;
        case 4: return 1200; break;
        default: return 0;
    }
}

bool save_point_to_list(char* name) {
    // 파일이 없어도 게임 실행 시 파일을 생성하므로 없으면 SAVE_FILE_EXCEPTION
    FILE *fp = fopen(filename, "r");
    if (!fp)
        return false;

    time_t t = time(NULL);
    struct tm *lt = localtime(&t);

    Result result;

    // name 버퍼크기 만큼 복사 후 맨 끝에 Null
    strncpy(result.name, name, sizeof(result.name) - 1);
    result.name[sizeof(result.name)-1] = '\0';
    result.point = point;
    result.year  = lt->tm_year + 1900;
    result.month = lt->tm_mon + 1;
    result.day   = lt->tm_mday;
    result.hour  = lt->tm_hour;
    result.min   = lt->tm_min;

    Node *new_node = make_node(&result);

    if (result_list == NULL) {
        result.rank = 1;
        result_list = new_node;
    }
    else {
        Node *prev = result_list;
        Node *curr = result_list->next;
        while(curr != NULL && curr->data.point >= result.point) {
            prev = curr;
            curr = curr->next;
        }
        if (curr != NULL) 
            new_node->data.rank = curr->data.rank;
        else
             new_node->data.rank = prev->data.rank + 1;

        prev->next = new_node;
        new_node->next = curr;
        // 뒤의 랭킹들을 갱신
        while (curr) {
            curr->data.rank += 1;
            curr = curr->next;
        }
    }
    list_length++;
    return true;
}

void save_point_to_file(void) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("points.txt 열기 실패");
        return;
    }
    Node *tmp = result_list;
    for (int i = 0; i < list_length; i++) {
        Result *r = &tmp->data;
        fprintf(fp, "%s %ld %04d %02d %02d %02d %02d %03d\n",
                r->name,
                r->point,
                r->year, r->month, r->day,
                r->hour, r->min,
                r->rank);
        tmp = tmp->next;
    }
}

bool load_point() {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fp = fopen(filename, "w+");
        return true;
    }
    
   while (true) {
        Result result;
        int scanned = fscanf(fp,
            "%29s %ld %04d %02d %02d %02d %02d %03d\n",
            result.name,
            &result.point,
            &result.year, &result.month, &result.day,
            &result.hour, &result.min,
            &result.rank);
        // 스캔된 것이 없으면 종료
        if (scanned == EOF) {
            break;
        }
        else if (scanned != 8) {
            return false;
        }
        Node *new_node = make_node(&result);
        if (result_list == NULL) result_list = new_node;
        else {
            Node* tmp = result_list;
            while (tmp->next != NULL) {
                tmp = tmp->next;
            }
            tmp->next = new_node;
        }
        list_length++;
    }
    fclose(fp);
    return true;
}