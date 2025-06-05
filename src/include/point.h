#ifndef SCORE_H
#define SCORE_H

/**
 * 점수 관련 로직들을 담당합니다.
 */

/// @brief 부서진 라인에 해당하는 점수를 부여합니다. (NES Tetris 기준 1라인 40, 2라인 100, 3라인 300, 4라인 1200)
/// @param lines 부서진 라인 수
/// @return 부서진 라인에 해당하는 점수
long point_for_line(int lines);
void save_score();
void load_score();

#endif