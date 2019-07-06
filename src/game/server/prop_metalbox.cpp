//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#include "cbase.h"
#include "props.h"


// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

#define DISSOLVES 1<<16

class CProp_Metalbox : public CPhysicsProp
{
public:
	DECLARE_CLASS( CProp_Metalbox, CPhysicsProp );
	DECLARE_DATADESC();

	CProp_Metalbox( void );
	virtual void Precache( void );
	virtual void Spawn( void );
	virtual int DrawDebugTextOverlays( void );
	void InputEnable( inputdata_t &inputdata );
	void InputDisable( inputdata_t &inputdata );
	bool m_bDissolves;

	CNetworkVar( bool, m_bEnabled );
};

BEGIN_DATADESC( CProp_Metalbox )
	DEFINE_FIELD( m_bEnabled, FIELD_BOOLEAN ),
	DEFINE_KEYFIELD( m_bDissolves, FIELD_BOOLEAN,"Dissolves"),
	DEFINE_INPUTFUNC( FIELD_VOID, "Enable", InputEnable ),
	DEFINE_INPUTFUNC( FIELD_VOID, "Disable", InputDisable )
END_DATADESC()

LINK_ENTITY_TO_CLASS( prop_metalbox, CProp_Metalbox );


CProp_Metalbox::CProp_Metalbox( void )
{
}

void CProp_Metalbox::Precache( void )
{
	BaseClass::Precache();
	PrecacheModel( m_ModelName.ToCStr() );
}

void CProp_Metalbox::Spawn( void )
{
	Precache();
	BaseClass::Spawn();
	SetModel( m_ModelName.ToCStr() );
}

void CProp_Metalbox::InputEnable( inputdata_t &inputdata )
{
	m_bEnabled = true;
}

void CProp_Metalbox::InputDisable( inputdata_t &inputdata )
{
	m_bEnabled = false;
}

//-----------------------------------------------------------------------------
// Draw debug overlays
//-----------------------------------------------------------------------------
int CProp_Metalbox::DrawDebugTextOverlays()
{
	int text_offset = BaseClass::DrawDebugTextOverlays();

	if (m_debugOverlays & OVERLAY_TEXT_BIT) 
	{
		char tempstr[255];

		Q_snprintf( tempstr, sizeof(tempstr), "%s", m_bEnabled ? "Enabled" : "Disabled" );
		EntityText( text_offset++, tempstr, 0 );
		
	}
	

	return text_offset;
}
