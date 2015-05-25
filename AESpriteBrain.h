#ifndef AE_SPRITE_COL
#define AE_SPRITE_COL

#include "AETypes.h"
#include "AEBasic.h"
#include "AESprite.h"
#include "AE_ClassWithType.h"
#include <boost/shared_ptr.hpp>

namespace AE
{
	class Spr;
	class CollisionEvents;
	
	class SpriteBrain : public ClassWithType
	{
		public:
			SpriteBrain();
			~SpriteBrain();
			
			virtual void avancer(DRect &);
		
			virtual void connect(boost::shared_ptr<Spr> &);
			virtual void disconnect();
			
			Type getType();
		
			virtual CollisionEvents thereIsCollision(CollisionEvents &);
			virtual void collisionWith(SpriteBrain &);
		
		private:
			boost::shared_ptr<Spr> m_sprite_connected_with;
	};
	
	typedef boost::shared_ptr<SpriteBrain> SpriteBrainPtr;
}

#endif
