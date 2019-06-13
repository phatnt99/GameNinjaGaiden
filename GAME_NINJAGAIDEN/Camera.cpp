#include "Camera.h"





Camera::Camera(int w, int h)
{
	_width = w;
	_height = h;
	isAllowFollowNinja = true;

	// Biên mặc định ban đầu là kích thước MAP
	_boundaryLeft = 0;
	_boundaryRight = 0;// (float)(MapWidth - SCREEN_WIDTH);
	_xCamBackup = _yCamBackup = 0;
	SetBoundaryBackup(_boundaryLeft, _boundaryRight);
	vx = 0;
}

Camera::~Camera()
{
}

void Camera::Update(DWORD dt)
{
	this->dt = dt;

	if (_xCam < _boundaryLeft)
		_xCam = _boundaryLeft;

	if (_xCam > _boundaryRight)
		_xCam = _boundaryRight;

}
D3DXVECTOR2 Camera::Transform(float xWorld, float yWorld)
{
	return D3DXVECTOR2(xWorld - _xCam , yWorld - _yCam);
}

void Camera::SetPosition(float x, float y)
{
	_xCam = x;
	_yCam = y;
}

float Camera::GetXCam()
{
	return _xCam;
}

float Camera::GetYCam()
{
	return _yCam;
}


int Camera::GetWidth()
{
	return _width;
}

int Camera::GetHeight()
{
	return _height;
}

bool Camera::checkObjectInCamera(float x, float y, float w, float h)
{
	if (x + w < _xCam || _xCam + _width < x)
		return false;
	if (y + h < _yCam || _yCam + _height < y)
		return false;
	return true;
}

bool Camera::AllowFollowNinja()
{
	return isAllowFollowNinja;
}

void Camera::SetAllowFollowNinja(bool b)
{
	isAllowFollowNinja = b;
}


void Camera::SetBoundary(float left, float right)
{
	_boundaryLeft = left;
	_boundaryRight = right;
}

float Camera::GetBoundaryRight()
{
	return _boundaryRight;
}

float Camera::GetBoundaryLeft()
{
	return _boundaryLeft;
}

void Camera::SetPositionBackup(float X, float Y)
{
	_xCamBackup = X;
	_yCamBackup = Y;

}

void Camera::SetBoundaryBackup(float l, float r)
{
	_boundaryLeftBackup = l;
	_boundaryRightBackup = r;
}

void Camera::RestoreBoundary()
{
	_boundaryLeft = _boundaryLeftBackup;
	_boundaryRight = _boundaryRightBackup;
}

void Camera::RestorePosition()
{
	_xCam = _xCamBackup;
	_yCam = _yCamBackup;

	_boundaryLeft = _boundaryLeftBackup;
	_boundaryRight = _boundaryRightBackup;


}
