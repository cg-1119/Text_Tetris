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

bool save_point(char* name) {
    if (!name) return true; // 이름이 없으면 저장하지 않고 종료

    // 게임 실행 시 파일을 생성하므로 없으면 SAVE_FILE_EXCEPTION
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
    fprintf(fp, "%s %ld %04d %02d %02d %02d %02d %02d\n",
            result.name, result.point, result.year, result.month, result.day, result.hour, result.min, result.rank);
    fclose(fp);

}
bool load_point() {
    FILE *fp = fopen(filename, "r");
    if (!fp)
        fp = fopen(filename, "w+");
        return true;
    
   while (true) {
        Result result;
        int scanned = fscanf(fp,
            "%s %ld %d %d %d %d %d %d\n",
            result.name,
            &result.point,
            &result.year, &result.month, &result.day,
            &result.hour, &result.min,
            &result.rank);
        // 스캔된 것이 없으면 종료
        if (scanned == 0) {
            break;
        }
        else if (scanned != 8) {
            return false;
        }
        Node* new_node = make_node(&result);
        if (result_list == NULL) result_list = new_node;
        else {
            Node* tmp = (Node*)result_list;
            while (true) {
                if (tmp->next != NULL)
                    tmp = tmp->next;
            }
            tmp->next = new_node;
        }
    }
    fclose(fp);
    return true;
}