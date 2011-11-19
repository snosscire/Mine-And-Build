#ifndef MINE_CAMERA_H
#define MINE_CAMERA_H

typedef struct _mine_camera Camera;

struct _mine_camera
{
	void (*destroy)(Camera*);
	void (*update)(Camera*);
	int  (*left)(Camera*);
	int  (*right)(Camera*);
	int  (*top)(Camera*);
	int  (*bottom)(Camera*);
	void *data;
};

Camera * MineCamera_Create();
void MineCamera_Destroy( Camera *camera );
void MineCamera_Update( Camera *camera );
int MineCamera_Left( Camera *camera );
int MineCamera_Right( Camera *camera );
int MineCamera_Top( Camera *camera );
int MineCamera_Bottom( Camera *camera );

#endif /* MINE_CAMERA_H */
