/**\file			sprite.cpp
 * \author			Chris Thielen (chris@epiar.net)
 * \date			Created: Unknown (2006?)
 * \date			Modified: Saturday, January 5, 2008
 * \brief
 * \details
 */

#include "includes.h"
#include "common.h"
#include "Sprites/sprite.h"
#include "Utilities/log.h"


// Sprite ID 0 is only used as a NULL
int Sprite::sprite_ids = 1;

/**\class Sprite
 * \brief Sprite handling. */

Sprite::Sprite() {
	id = sprite_ids++;

	// Momentum caps

	angle = 0.;
	
	image = NULL;
	
	radarSize = 1;
	radarColor = Color::Get(0.7f, 0.7f, 0.7f);
}

Coordinate Sprite::GetWorldPosition( void ) const {
	return worldPosition;
}

void Sprite::SetWorldPosition( Coordinate coord ) {
	worldPosition = coord;
}

void Sprite::Update( void ) {
	// Apply their momentum to change their coordinates
	worldPosition += momentum;
	
	// update acceleration
	acceleration = lastMomentum - momentum; 
	lastMomentum = momentum;
}

// sprites are drawn centered on wx,wy by design of Image
void Sprite::Draw( void ) {
	int wx, wy;

	wx = worldPosition.GetScreenX();
	wy = worldPosition.GetScreenY();
	
	if( image ) {
		image->DrawCentered( wx, wy, angle );
	} else {
		LogMsg(WARN, "Attempt to draw a sprite before an image was assigned." );
	}
}

bool compareSpritePtrs(Sprite* a, Sprite* b){
	if(a->GetDrawOrder() != b->GetDrawOrder()) {
		return a->GetDrawOrder() < b->GetDrawOrder();
	} else {
		return a->GetID() < b->GetID();
	}
}

