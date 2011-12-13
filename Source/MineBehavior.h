#ifndef MINE_BEHAVIOR_H
#define MINE_BEHAVIOR_H

typedef struct __mine_behavior Behavior;

struct __mine_object;
struct __mine_world;

struct __mine_behavior
{
	void (*perform)(struct __mine_object*,unsigned int);
};

Behavior * MineBehavior_Create();
void MineBehavior_Destroy( Behavior *behavior );
void MineBehavior_Perform( Behavior *behavior, struct __mine_object *object, unsigned int delta_time );

#endif /* MINE_BEHAVIOR_H */
