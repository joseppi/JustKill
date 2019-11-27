#pragma once

struct GameObject
{
	void newReplicationState(vec2 position, float angle);
	void Interpolate();

	// Transform component
	vec2 position = vec2{ 0.0f, 0.0f };

	// Render component
	vec2 pivot = vec2{ 0.5f, 0.5f };
	vec2 size = vec2{ 0.0f, 0.0f }; // NOTE(jesus): If equals 0, it takes the size of the texture
	float angle = 0.0f;
	vec4 color = vec4{ 1.0f, 1.0f, 1.0f, 1.0f }; // NOTE(jesus): The texture will tinted with this color
	Texture * texture = nullptr;
	int  order = 0;          // NOTE(jesus): determines the drawing order

	// For entity interpolation
	vec2 initial_position = vec2{ 0.0f, 0.0f };
	float initial_angle = 0.0f;

	vec2 final_position = vec2{ 0.0f, 0.0f };
	float final_angle = 0.0f;

	float interpolationSecondsElapsed = 0.0f;	

	// Animation component
	Animation* animation = nullptr;

	// Collider component
	Collider *collider = nullptr;

	// "Script" component
	Behaviour *behaviour = nullptr;

	// Network identity component
	uint32 networkId = 0; // NOTE(jesus): Only for network game objects

	// NOTE(jesus): Don't use in gameplay systems (use Instantiate, Destroy instead)
	enum State { NON_EXISTING, CREATING, UPDATING, DESTROYING };
	State state = NON_EXISTING;

	// Tag for custom usage
	uint32 tag = 0;

	// Detect the player inside the client
	bool isPlayer = false;

	// Last input sequence number for client prediction
	uint32 lastServerInputSN = 0;
	
private:

	void * operator new(size_t size) = delete;
	void operator delete (void *obj) = delete;

	void releaseComponents();
	friend class ModuleGameObject;
};

class ModuleGameObject : public Module
{
public:

	// Virtual functions

	bool init() override;

	bool preUpdate() override;

	bool update() override;

	bool postUpdate() override;

	bool cleanUp() override;

	static GameObject * Instantiate();

	static void Destroy(GameObject * gameObject);

	GameObject gameObjects[MAX_GAME_OBJECTS] = {};

	bool interpolateEntities = false;
};


// NOTE(jesus): These functions are named after Unity functions

GameObject *Instantiate();

void Destroy(GameObject *gameObject);