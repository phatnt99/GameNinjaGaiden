#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "define.h" 

class Camera
{
protected:
	float _xCam;
	float _yCam;

	float _xCamBackup;
	float _yCamBackup;
	float _boundaryLeftBackup;
	float _boundaryRightBackup;

	int _width;
	int _height;

	float _boundaryLeft; // biên giới hạn bên trái 
	float _boundaryRight; // biên giới hạn bên phải

	float vx;
	DWORD dt;

	bool isAllowFollowNinja;

public:
	Camera(int w, int h);
	~Camera();

	void Update(DWORD dt);

	D3DXVECTOR2 Transform(float, float);

	void SetPosition(float x, float y);

	float GetXCam();
	float GetYCam();
	int GetWidth();
	int GetHeight();

	bool checkObjectInCamera(float x, float y, float w, float h);

	bool AllowFollowNinja();
	void SetAllowFollowNinja(bool b);

	void SetBoundary(float left, float right); // set biên giới hạn cho camera
	float GetBoundaryRight();
	float GetBoundaryLeft();

	void SetPositionBackup(float X, float Y);
	void RestorePosition();

	void SetBoundaryBackup(float l, float r);
	void RestoreBoundary();
};

#endif



