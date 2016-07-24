#pragma once

#include <d3dx9.h>

class CFPCamera
{
private:
	D3DXVECTOR3 m_position; // позици€
	float m_yaw;  //вокруг y
	float m_pitch; // вокруг х
	float m_roll; // вокруг z
	D3DXVECTOR3 m_up, m_look, m_right; // оси

	float RestrictAngleTo360Range(float angle) const;
public:
	CFPCamera(D3DXVECTOR3 startPos);
	~CFPCamera(void);

	void CalculateViewMatrix(D3DXMATRIX *viewMatrix);

	float GetYaw() const { return m_yaw; }
	float GetPitch() const { return m_pitch; }
	float GetRoll() const { return m_roll; }
	D3DXVECTOR3 GetPosition() const { return m_position; }

	// ƒвижение
	void MoveForward(float amount) { m_position += m_look*amount; }
	void MoveRight(float amount) { m_position += m_right*amount; }
	void MoveUp(float amount) { m_position += m_up*amount; }

	// ѕоворот
	void Yaw(float amount); // поворот по оси x
	void Pitch(float amount); // поворот по оси y	
	void Roll(float amount); // поворот по оси z	
};
