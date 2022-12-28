////////////////////////////////////////////////////////////////////////////////
//
// File: virtualLego.cpp
//
// Original Author: ¹ÚÃ¢Çö Chang-hyeon Park, 
// Modified by Bong-Soo Sohn and Dong-Jun Kim
// 
// Originally programmed for Virtual LEGO. 
// Modified later to program for Virtual Billiard.
// 
////////////////////////////////////////////////////////////////////////////////

#include "d3dUtility.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <cassert>

IDirect3DDevice9* Device = NULL;

// window size
const int Width = 1024;
const int Height = 768;

// initialize the position of smiley ball
const float spherePos[33][2] = { 
	{-2.56f, 0}, {2.56f, 0}, {0, -2.56f}, {0, 2.56f}, {-2.56f, -0.82f}, {2.56f, -0.82f}, {-2.56f, 0.82f}, {2.56f, 0.82f},
	{-1.95f, -1.52f}, {1.95f, -1.52f}, {-1.95f, 1.52f}, {1.95f, 1.52f}, {-1.32f, -2.12f}, {1.32f, -2.12f}, {-1.32f, 2.12f}, {1.32f, 2.12f},
	{-0.71f, -2.51f}, {0.71f, -2.51f}, {-0.71f, 2.51f}, {0.71f, 2.51f},
	{-1, -1.3f},{-1, 1.3f}, {-0.5, -1.3f},{-0.5, 1.3f},
	{0, 0}, {0.5f, 0},
	{0.71f, -1.5f}, {0.71f, 1.5f}, {1.11f, -1.0f}, {1.61f, 0}, {1.11f, 1.0f}, {1.51f, 0.5f}, {1.51f, -0.5f}};
	

// -----------------------------------------------------------------------------
// Transform matrices
// -----------------------------------------------------------------------------
D3DXMATRIX g_mWorld;
D3DXMATRIX g_mView;
D3DXMATRIX g_mProj;

#define M_RADIUS 0.21   // ball radius
#define PI 3.14159265
#define M_HEIGHT 0.01
#define DECREASE_RATE 0.9982 

// -----------------------------------------------------------------------------
// CSphere class definition
// -----------------------------------------------------------------------------

class CSphere {
	private:
		float					center_x, center_y, center_z;
		float                   m_radius;
		float					m_velocity_x;
		float					m_velocity_z;

	public:
		CSphere(void)
		{
			D3DXMatrixIdentity(&m_mLocal);
			ZeroMemory(&m_mtrl, sizeof(m_mtrl));
			m_radius = 0;
			m_velocity_x = 0;
			m_velocity_z = 0;
			m_pSphereMesh = NULL;
		}
		~CSphere(void) {}

	public:
		bool create(IDirect3DDevice9* pDevice, D3DXCOLOR color = d3d::WHITE)
		{
			if (NULL == pDevice)
				return false;

			m_mtrl.Ambient = color;
			m_mtrl.Diffuse = color;
			m_mtrl.Specular = color;
			m_mtrl.Emissive = d3d::BLACK;
			m_mtrl.Power = 5.0f;

			if (FAILED(D3DXCreateSphere(pDevice, getRadius(), 50, 50, &m_pSphereMesh, NULL)))
				return false;
			return true;
		}

		void destroy(void)
		{
			if (m_pSphereMesh != NULL) {
				m_pSphereMesh->Release();
				m_pSphereMesh = NULL;
			}
		}

		void draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld)
		{
			if (NULL == pDevice)
				return;
			pDevice->SetTransform(D3DTS_WORLD, &mWorld);
			pDevice->MultiplyTransform(D3DTS_WORLD, &m_mLocal);
			pDevice->SetMaterial(&m_mtrl);
			m_pSphereMesh->DrawSubset(0);
		}

		bool hasIntersected(CSphere& ball) 
		{
			// Insert your code here.
			// Calculate the distance between two spheres.
			D3DXVECTOR3 dis_center = ball.getCenter() - this->getCenter();
			
			double dis_total = sqrt(dis_center.x * dis_center.x + dis_center.z * dis_center.z);

			if (dis_total < 2 * M_RADIUS)
				return true;

			return false;
		}

		void hitBy(CSphere& ball) 
		{ 
			// Insert your code here.
			// Change the velocity of the sphere to bounce off.
			
			if (this->hasIntersected(ball)) {
				D3DXVECTOR3 dis_center = ball.getCenter() - this->getCenter();
				double dis_x = dis_center.x;
				double dis_z = dis_center.z;

				double vel_x = ball.getVelocity_X();
				double vel_z = ball.getVelocity_Z();

				double new_vel_x = dis_x * sqrt((vel_x * vel_x + vel_z * vel_z) / (dis_x * dis_x + dis_z * dis_z));
				double new_vel_z = dis_z * sqrt((vel_x * vel_x + vel_z * vel_z) / (dis_x * dis_x + dis_z * dis_z));
				ball.setPower(new_vel_x, new_vel_z);
			}
		}

		void ballUpdate(float timeDiff)
		{
			const float TIME_SCALE = 3.3;
			D3DXVECTOR3 cord = this->getCenter();
			double vx = abs(this->getVelocity_X());
			double vz = abs(this->getVelocity_Z());

			if (vx > 0.01 || vz > 0.01)
			{

				float tX = cord.x + TIME_SCALE * timeDiff * m_velocity_x;
				float tZ = cord.z + TIME_SCALE * timeDiff * m_velocity_z;
			
				//correction of position of ball
				/* Please uncomment this part because this correction of ball position is necessary when a ball collides with a wall
				if(tX >= (4.5 - M_RADIUS))
					tX = 4.5 - M_RADIUS;
				else if(tX <=(-4.5 + M_RADIUS))
					tX = -4.5 + M_RADIUS;
				else if(tZ <= (-3 + M_RADIUS))
					tZ = -3 + M_RADIUS;
				else if(tZ >= (3 - M_RADIUS))
					tZ = 3 - M_RADIUS;
				*/

				this->setCenter(tX, cord.y, tZ);
			}
			else { this->setPower(0, 0); }
			//this->setPower(this->getVelocity_X() * DECREASE_RATE, this->getVelocity_Z() * DECREASE_RATE);
		}

		double getVelocity_X() { return this->m_velocity_x; }
		double getVelocity_Z() { return this->m_velocity_z; }

		void setPower(double vx, double vz)
		{
			this->m_velocity_x = vx;
			this->m_velocity_z = vz;
		}

		void setCenter(float x, float y, float z)
		{
			D3DXMATRIX m;
			center_x = x;	center_y = y;	center_z = z;
			D3DXMatrixTranslation(&m, x, y, z);
			setLocalTransform(m);
		}

		float getRadius(void)  const { return (float)(M_RADIUS); }
		const D3DXMATRIX& getLocalTransform(void) const { return m_mLocal; }
		void setLocalTransform(const D3DXMATRIX& mLocal) { m_mLocal = mLocal; }
		D3DXVECTOR3 getCenter(void) const
		{
			D3DXVECTOR3 org(center_x, center_y, center_z);
			return org;
		}

	private:
		D3DXMATRIX              m_mLocal;
		D3DMATERIAL9            m_mtrl;
		ID3DXMesh* m_pSphereMesh;

};



// -----------------------------------------------------------------------------
// CWall class definition
// -----------------------------------------------------------------------------

class CWall {

private:

	float					m_x;
	float					m_z;
	float                   m_width;
	float                   m_depth;
	float					m_height;

public:
	CWall(void)
	{
		D3DXMatrixIdentity(&m_mLocal);
		ZeroMemory(&m_mtrl, sizeof(m_mtrl));
		m_width = 0;
		m_depth = 0;
		m_pBoundMesh = NULL;
	}
	~CWall(void) {}
public:
	bool create(IDirect3DDevice9* pDevice, float ix, float iz, float iwidth, float iheight, float idepth, D3DXCOLOR color = d3d::WHITE)
	{
		if (NULL == pDevice)
			return false;

		m_mtrl.Ambient = color;
		m_mtrl.Diffuse = color;
		m_mtrl.Specular = color;
		m_mtrl.Emissive = d3d::BLACK;
		m_mtrl.Power = 5.0f;

		m_width = iwidth;
		m_depth = idepth;

		if (FAILED(D3DXCreateBox(pDevice, iwidth, iheight, idepth, &m_pBoundMesh, NULL)))
			return false;
		return true;
	}
	void destroy(void)
	{
		if (m_pBoundMesh != NULL) {
			m_pBoundMesh->Release();
			m_pBoundMesh = NULL;
		}
	}
	void draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld)
	{
		if (NULL == pDevice)
			return;
		pDevice->SetTransform(D3DTS_WORLD, &mWorld);
		pDevice->MultiplyTransform(D3DTS_WORLD, &m_mLocal);
		pDevice->SetMaterial(&m_mtrl);
		m_pBoundMesh->DrawSubset(0);
	}

	bool hasIntersected(CSphere& ball) { 
		// Insert your code here.
		//walls have additional margin of ball's Radius
		float left_wall = this->getPosition().z - this->getDepth() / 2 - M_RADIUS;
		float right_wall = this->getPosition().z + this->getDepth() / 2 + M_RADIUS;
		float top_wall = this->getPosition().x - this->getWidth() / 2 - 2 * M_RADIUS;
		float bottom_wall = this->getPosition().x + this->getWidth() / 2 + 2 * M_RADIUS;

		if (top_wall <= ball.getCenter().x && ball.getCenter().x <= bottom_wall) {
			if (left_wall <= ball.getCenter().z && ball.getCenter().z <= right_wall)
				return true;
			else
				return false;
		}
		else 
			return false;
	}

	void hitBy(CSphere& ball) { 
		// Insert your code here.
		if (this->hasIntersected(ball)) {

			float left_wall = this->getPosition().z - this->getDepth() / 2 - M_RADIUS;
			float right_wall = this->getPosition().z + this->getDepth() / 2 + M_RADIUS;
			float top_wall = this->getPosition().x - this->getWidth() / 2 - 2 * M_RADIUS;
			float bottom_wall = this->getPosition().x + this->getWidth() / 2 + 2 * M_RADIUS;

			float ball_x = ball.getCenter().x;
			float ball_y = ball.getCenter().y;
			float ball_z = ball.getCenter().z;

			if ((top_wall <= ball_x - 2 * M_RADIUS && ball_x + 2 * M_RADIUS <= bottom_wall) == false &&
				(left_wall <= ball_z - M_RADIUS && ball_z + M_RADIUS <= right_wall)) {
				if (left_wall <= ball_x && ball_x <= this->getPosition().x)
					ball_x = top_wall;
				else
					ball_x = bottom_wall;
				ball.setPower(-ball.getVelocity_X(), ball.getVelocity_Z());
			}

			if ((top_wall <= ball_x - 2 * M_RADIUS && ball_x + 2 * M_RADIUS <= bottom_wall) &&
				(left_wall <= ball_z - M_RADIUS && ball_z + M_RADIUS <= right_wall) == false) {
				if (top_wall <= ball_z && ball_z <= this->getPosition().z)
					ball_z = left_wall;
				else 
					ball_z = right_wall;
				ball.setPower(ball.getVelocity_X(), -ball.getVelocity_Z());
			}
			ball.setCenter(ball_x, ball_y, ball_z);
		}
	}

	void setPosition(float x, float y, float z)
	{
		D3DXMATRIX m;
		this->m_x = x;
		this->m_z = z;

		D3DXMatrixTranslation(&m, x, y, z);
		setLocalTransform(m);
	}

	D3DXVECTOR3 getPosition(void) const { 
		D3DXVECTOR3 wallPos(m_x, 0, m_z);
		return wallPos;
	}
	float getWidth(void) const { return m_width; }
	float getHeight(void) const { return M_HEIGHT; }
	float getDepth(void) const { return m_depth; }



private:
	void setLocalTransform(const D3DXMATRIX& mLocal) { m_mLocal = mLocal; }

	D3DXMATRIX              m_mLocal;
	D3DMATERIAL9            m_mtrl;
	ID3DXMesh* m_pBoundMesh;
};

// -----------------------------------------------------------------------------
// CLight class definition
// -----------------------------------------------------------------------------

class CLight {
public:
	CLight(void)
	{
		static DWORD i = 0;
		m_index = i++;
		D3DXMatrixIdentity(&m_mLocal);
		::ZeroMemory(&m_lit, sizeof(m_lit));
		m_pMesh = NULL;
		m_bound._center = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_bound._radius = 0.0f;
	}
	~CLight(void) {}
public:
	bool create(IDirect3DDevice9* pDevice, const D3DLIGHT9& lit, float radius = 0.1f)
	{
		if (NULL == pDevice)
			return false;
		if (FAILED(D3DXCreateSphere(pDevice, radius, 10, 10, &m_pMesh, NULL)))
			return false;

		m_bound._center = lit.Position;
		m_bound._radius = radius;

		m_lit.Type = lit.Type;
		m_lit.Diffuse = lit.Diffuse;
		m_lit.Specular = lit.Specular;
		m_lit.Ambient = lit.Ambient;
		m_lit.Position = lit.Position;
		m_lit.Direction = lit.Direction;
		m_lit.Range = lit.Range;
		m_lit.Falloff = lit.Falloff;
		m_lit.Attenuation0 = lit.Attenuation0;
		m_lit.Attenuation1 = lit.Attenuation1;
		m_lit.Attenuation2 = lit.Attenuation2;
		m_lit.Theta = lit.Theta;
		m_lit.Phi = lit.Phi;
		return true;
	}
	void destroy(void)
	{
		if (m_pMesh != NULL) {
			m_pMesh->Release();
			m_pMesh = NULL;
		}
	}
	bool setLight(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld)
	{
		if (NULL == pDevice)
			return false;

		D3DXVECTOR3 pos(m_bound._center);
		D3DXVec3TransformCoord(&pos, &pos, &m_mLocal);
		D3DXVec3TransformCoord(&pos, &pos, &mWorld);
		m_lit.Position = pos;

		pDevice->SetLight(m_index, &m_lit);
		pDevice->LightEnable(m_index, TRUE);
		return true;
	}

	void draw(IDirect3DDevice9* pDevice)
	{
		if (NULL == pDevice)
			return;
		D3DXMATRIX m;
		D3DXMatrixTranslation(&m, m_lit.Position.x, m_lit.Position.y, m_lit.Position.z);
		pDevice->SetTransform(D3DTS_WORLD, &m);
		pDevice->SetMaterial(&d3d::WHITE_MTRL);
		m_pMesh->DrawSubset(0);
	}

	D3DXVECTOR3 getPosition(void) const { return D3DXVECTOR3(m_lit.Position); }

private:
	DWORD               m_index;
	D3DXMATRIX          m_mLocal;
	D3DLIGHT9           m_lit;
	ID3DXMesh* m_pMesh;
	d3d::BoundingSphere m_bound;
};


// -----------------------------------------------------------------------------
// Global variables
// -----------------------------------------------------------------------------
CWall	g_legoPlane;
CWall	g_legowall[4]; 
CLight	g_light;
CSphere	g_target_ball[33]; // It destroyed when hit by the red ball
CSphere g_red_ball; // It hits target balls
CSphere	g_white_ball; // It hits red ball 

bool isReset = true; // check if the game is initialized
double g_camera_pos[3] = { 0.0, -5.0, 8.0 };

// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------


void destroyAllLegoBlock(void)
{
}

// initialization
bool Setup()
{
	int i;

	D3DXMatrixIdentity(&g_mWorld);
	D3DXMatrixIdentity(&g_mView);
	D3DXMatrixIdentity(&g_mProj);

	// create plane and set the position
	if (false == g_legoPlane.create(Device, -1, -1, 9, 0.03f, 6, d3d::GREEN)) return false;
	g_legoPlane.setPosition(0.0f, -0.0006f / 5, 0.0f);

	// create walls and set the position. note that there are three walls
	if (false == g_legowall[0].create(Device, -1, -1, 9, 0.3f, 0.12f, d3d::DARKRED)) return false;
	g_legowall[0].setPosition(0.0f, 0.12f, 3.06f);
	if (false == g_legowall[1].create(Device, -1, -1, 9, 0.3f, 0.12f, d3d::DARKRED)) return false;
	g_legowall[1].setPosition(0.0f, 0.12f, -3.06f);
	if (false == g_legowall[2].create(Device, -1, -1, 0.12f, 0.5f, 6.24f, d3d::DARKRED)) return false;
	g_legowall[2].setPosition(-4.56f, 0.12f, 0.0f);
	if (false == g_legowall[3].create(Device, -1, -1, 0.12f, 0.3f, 6.24f, d3d::DARKRED)) return false;
	g_legowall[3].setPosition(4.56f, 0.12f, 0.0f);


	// create target yellow balls and set the position
	for (i = 0; i < 33; i++) {
		if (false == g_target_ball[i].create(Device, d3d::YELLOW)) return false;
		g_target_ball[i].setCenter(spherePos[i][0], (float)M_RADIUS, spherePos[i][1]);
		g_target_ball[i].setPower(0, 0);
	}

	// create white ball for hitting the red ball
	if (false == g_white_ball.create(Device, d3d::WHITE)) return false;
	g_white_ball.setCenter(4.5f, 0.5, (float)M_RADIUS);

	// create red ball for destroying target balls
	if (false == g_red_ball.create(Device, d3d::RED)) return false;
	g_red_ball.setCenter(4.5f - 0.43, 0.5, (float)M_RADIUS);

	// light setting 
	D3DLIGHT9 lit;
	::ZeroMemory(&lit, sizeof(lit));
	lit.Type = D3DLIGHT_POINT;
	lit.Diffuse = d3d::WHITE;
	lit.Specular = d3d::WHITE * 0.9f;
	lit.Ambient = d3d::WHITE * 0.9f;
	lit.Position = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
	lit.Range = 100.0f;
	lit.Attenuation0 = 0.0f;
	lit.Attenuation1 = 0.9f;
	lit.Attenuation2 = 0.0f;
	if (false == g_light.create(Device, lit))
		return false;

	// Position and aim the camera.
	D3DXVECTOR3 pos(10.0f, 10.0f, 0.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 2.0f, 0.0f);
	D3DXMatrixLookAtLH(&g_mView, &pos, &target, &up);
	Device->SetTransform(D3DTS_VIEW, &g_mView);

	// Set the projection matrix.
	D3DXMatrixPerspectiveFovLH(&g_mProj, D3DX_PI / 4,
		(float)Width / (float)Height, 1.0f, 100.0f);
	Device->SetTransform(D3DTS_PROJECTION, &g_mProj);

	// Set render states.
	Device->SetRenderState(D3DRS_LIGHTING, TRUE);
	Device->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	Device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

	g_light.setLight(Device, g_mWorld);
	return true;
}

void Cleanup(void)
{
	g_legoPlane.destroy();
	for (int i = 0; i < 4; i++) {
		g_legowall[i].destroy();
	}
	destroyAllLegoBlock();
	g_light.destroy();
}


// timeDelta represents the time between the current image frame and the last image frame.
// the distance of moving balls should be "velocity * timeDelta"
bool Display(float timeDelta)
{
	int i = 0;
	
	if (Device)
	{
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00afafaf, 1.0f, 0);
		Device->BeginScene();

		for (i = 0; i < 33; i++) {
			g_target_ball[i].ballUpdate(timeDelta);
			g_target_ball[i].hitBy(g_red_ball);
			// Send the ball out of the plane position.
			if (g_target_ball[i].hasIntersected(g_red_ball))
				g_target_ball[i].setCenter(-100.0f, 0, -100.0f);
		}

		g_red_ball.ballUpdate(timeDelta);

		for (i = 0; i < 3; i++) {
			g_legowall[i].hitBy(g_red_ball);
		}

		g_white_ball.ballUpdate(timeDelta);
		g_white_ball.hitBy(g_red_ball);

		// Check red ball out of the plane and set the position again.
		if (g_red_ball.getCenter().x >= 4.5f) {
			isReset = true;
			g_white_ball.setCenter(g_white_ball.getCenter().x, g_white_ball.getCenter().y, g_white_ball.getCenter().z);
			g_red_ball.setCenter(g_white_ball.getCenter().x - 0.43, g_white_ball.getCenter().y, g_white_ball.getCenter().z);
			g_red_ball.setPower(0, 0);

			for (i = 0; i < 33; i++) {
				g_target_ball[i].setCenter(spherePos[i][0], (float)M_RADIUS, spherePos[i][1]);
				g_target_ball[i].setPower(0, 0);
			}
		}
		// draw plane, walls, and spheres
		g_legoPlane.draw(Device, g_mWorld);
		for (i = 0; i < 3; i++) {
			g_legowall[i].draw(Device, g_mWorld);
		}

		for (i = 0; i < 33; i++) {
			g_target_ball[i].draw(Device, g_mWorld);
		}
		g_white_ball.draw(Device, g_mWorld);
		g_red_ball.draw(Device, g_mWorld);
		g_light.draw(Device);

		Device->EndScene();
		Device->Present(0, 0, 0, 0);
		Device->SetTexture(0, NULL);
	}
	return true;
}


LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static bool wire = false;
	static int old_x = 0;
	static int old_y = 0;
	static enum { WORLD_MOVE, LIGHT_MOVE, BLOCK_MOVE } move = WORLD_MOVE;
	
	switch (msg) {
	case WM_DESTROY:
	{
		::PostQuitMessage(0);
		break;
	}
	case WM_KEYDOWN:
	{
		switch (wParam) {
		case VK_ESCAPE:
			::DestroyWindow(hwnd);
			break;
		case VK_RETURN:
			if (NULL != Device) {
				wire = !wire;
				Device->SetRenderState(D3DRS_FILLMODE,
					(wire ? D3DFILL_WIREFRAME : D3DFILL_SOLID));
			}
			break;
		case VK_SPACE: 
			g_white_ball.setCenter(g_white_ball.getCenter().x, g_white_ball.getCenter().y, g_white_ball.getCenter().z);
			g_red_ball.setCenter(g_white_ball.getCenter().x - 0.43, g_white_ball.getCenter().y, g_white_ball.getCenter().z);
			g_red_ball.setPower(-2.2, 0.0);
			isReset = false;
		}
		break;
	}
	case WM_MOUSEMOVE:
	{
		int new_x = LOWORD(lParam);
		
		float right_wall = g_legowall[0].getPosition().z - g_legowall[0].getDepth() / 2 - M_RADIUS;
		float left_wall = g_legowall[1].getPosition().z + g_legowall[1].getDepth() / 2 + M_RADIUS;

		if (LOWORD(wParam) & MK_LBUTTON) {
			float new_z = g_white_ball.getCenter().z + (old_x - new_x) * (-0.007f);

			if (new_z < left_wall) 
				new_z = left_wall;
			else if (new_z > right_wall) 
				new_z = right_wall;
			old_x = new_x;
		
			move = WORLD_MOVE;
			
			if (isReset)
				g_red_ball.setCenter(g_white_ball.getCenter().x - 0.43, g_white_ball.getCenter().y, new_z);
			g_white_ball.setCenter(g_white_ball.getCenter().x, g_white_ball.getCenter().y, new_z);
		}
		break;
	}
	}

	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE prevInstance,
	PSTR cmdLine,
	int showCmd)
{
	srand(static_cast<unsigned int>(time(NULL)));

	if (!d3d::InitD3D(hinstance,
		Width, Height, true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, "InitD3D() - FAILED", 0, 0);
		return 0;
	}

	if (!Setup())
	{
		::MessageBox(0, "Setup() - FAILED", 0, 0);
		return 0;
	}

	d3d::EnterMsgLoop(Display);

	Cleanup();

	Device->Release();

	return 0;
}