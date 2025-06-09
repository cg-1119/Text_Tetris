#ifndef SCORE_H
#define SCORE_H

#include <stdbool.h>

/**
 * 점수 관련 로직들을 담당합니다.
 */

/// @brief 부서진 라인에 해당하는 점수를 부여합니다. (NES Tetris 기준 1라인 40, 2라인 100, 3라인 300, 4라인 1200)
/// @param lines 부서진 라인 수
/// @return 부서진 라인에 해당하는 점수
long point_for_line(int lines);

/// @brief result_list에 게임 정보를 저장합니다,
/// @param name 저장 할 이름
/// @return 성공 여부의 boolean
bool save_point_to_list(char *name);

// 게임 종료 시 파일에 포인트 정보를 저장합니다.
void save_point_to_file(void);

/// @brief 포인트 정보를 불러오고, 최고 점수를 업데이트 합니다. 만약 불러오기를 실패한다면 예외를 일으킵니다.
/// @return 성공 여부의 boolean
bool load_point();

#endif // SCORE_H