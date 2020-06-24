#ifdef __cplusplus
extern "C" {
#endif

#ifndef __TYPES_C_H__
#define __TYPES_C_H__

#define BUFFER_SIZE 1920 * 1080 * 3
#define ROI_MAX 4
#define PERSON_MAX 200

typedef struct Point {
  int x;
  int y;
} Point;

typedef struct Box {
  int left_up_hor;      //左上x 坐标
  int left_up_ver;      //左上y 坐标
  int right_bottom_hor; // 右下x 坐标
  int right_bottom_ver; // 右下y 坐标
} Box;

typedef struct ImageShared {
  char cam_id[64]; //相机id 以'\0' 结尾字符串
  int64_t time_stamp;  //时间戳
  int width;       //图像宽
  int height;      // 图像高
  int roi_num;     // 相机roi 个数
  Box rois[ROI_MAX]; // 相机roi, 每个index对应一个roi, 有效个数由 roi_num决定
  unsigned char rgb[BUFFER_SIZE];  //
} ImageShared;

typedef struct Recoder {
  char cam_id[64];
  int64_t time_stamp;
  int roi_num;
  int person_num[ROI_MAX];
  Box box[ROI_MAX][PERSON_MAX];
} Recoder;

#endif

#ifdef __cplusplus
}
#endif