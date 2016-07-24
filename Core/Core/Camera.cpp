#include "Camera.h"

CFPCamera::CFPCamera(D3DXVECTOR3 startPos) : m_position(startPos), m_yaw(0), m_pitch(0), m_roll(0)
{
	// ортагональные оси
	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_look = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
}

CFPCamera::~CFPCamera(void)
{
}

void CFPCamera::CalculateViewMatrix(D3DXMATRIX *viewMatrix)
{
	

	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_look = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);


	D3DXMATRIX yawMatrix;
	D3DXMatrixRotationAxis(&yawMatrix, &m_up, m_yaw);

	D3DXVec3TransformCoord(&m_look, &m_look, &yawMatrix);
	D3DXVec3TransformCoord(&m_right, &m_right, &yawMatrix);


	D3DXMATRIX pitchMatrix;
	D3DXMatrixRotationAxis(&pitchMatrix, &m_right, m_pitch);

	D3DXVec3TransformCoord(&m_look, &m_look, &pitchMatrix);
	D3DXVec3TransformCoord(&m_up, &m_up, &pitchMatrix);


	D3DXMATRIX rollMatrix;
	D3DXMatrixRotationAxis(&rollMatrix, &m_look, m_roll);
	
	D3DXVec3TransformCoord(&m_right, &m_right, &rollMatrix);
	D3DXVec3TransformCoord(&m_up, &m_up, &rollMatrix);

	D3DXMatrixIdentity(viewMatrix);

	viewMatrix->_11 = m_right.x; viewMatrix->_12 = m_up.x; viewMatrix->_13 = m_look.x;
	viewMatrix->_21 = m_right.y; viewMatrix->_22 = m_up.y; viewMatrix->_23 = m_look.y;
	viewMatrix->_31 = m_right.z; viewMatrix->_32 = m_up.z; viewMatrix->_33 = m_look.z;

	viewMatrix->_41 = -D3DXVec3Dot(&m_position, &m_right);
	viewMatrix->_42 = -D3DXVec3Dot(&m_position, &m_up);
	viewMatrix->_43 = -D3DXVec3Dot(&m_position, &m_look);
}

void CFPCamera::Yaw(float amount)
{
	m_yaw += amount;
	m_yaw = RestrictAngleTo360Range(m_yaw);
}

void CFPCamera::Pitch(float amount)
{
	m_pitch += amount;
	m_pitch = RestrictAngleTo360Range(m_pitch);
}

void CFPCamera::Roll(float amount)
{
	m_roll += amount;
	m_roll = RestrictAngleTo360Range(m_roll);
}

float CFPCamera::RestrictAngleTo360Range(float angle) const
{
	while (angle>2 * D3DX_PI)
		angle -= 2 * D3DX_PI;

	while (angle<0)
		angle += 2 * D3DX_PI;

	return angle;
}