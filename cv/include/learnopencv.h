#ifndef CV_LEARNOPENCV_H_
#define CV_LEARNOPENCV_H_

/* �ڶ��� OpenCV��̽ */
extern int showimage(int argc, char *argv[]);
extern int showvideo(int argc, char *argv[]);
extern int ctrlvideo(int argc, char *argv[]);
extern int imageblur(int argc, char *argv[]);
extern int imagedown(int argc, char *argv[]);
extern int imagecanny(int argc, char *argv[]);
extern int openmedia(int argc, char *argv[]);
extern int writeavi(int argc, char *argv[]);

/* ������ ������� */
extern int cvaddweight(int argc, char *argv[]);

/*��ʮ�� �˲�����*/
extern int cvthreshold(int argc, char *argv[]);
extern int cvadapterthreshold(int argc, char *argv[]);

#endif 