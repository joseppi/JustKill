#include "Networks.h"
#include "ReplicationManagerClient.h"

void ReplicationManagerClient::read(const InputMemoryStream & packet, uint32 clientNetworkId)
{
	while (packet.RemainingByteCount() > 0)
	{
		uint32 networkId;
		packet >> networkId;
		ReplicationAction action;
		packet >> action;
		if (action == ReplicationAction::Create)
		{
			GameObject* go = nullptr;
			go = App->modLinkingContext->getNetworkGameObject(networkId, true);
			if (go != nullptr)
			{
				App->modLinkingContext->unregisterNetworkGameObject(go);
				Destroy(go);
			}

			go = Instantiate();
			App->modLinkingContext->registerNetworkGameObjectWithNetworkId(go, networkId);

			packet >> go->position.x;
			packet >> go->position.y;
			packet >> go->size.x;
			packet >> go->size.y;
			packet >> go->angle;
			packet >> go->order;
			if (networkId == clientNetworkId)
				go->isPlayer = true;

			if (go->isPlayer)
			{
				go->behaviour = new Player();
				go->behaviour->gameObject = go;
				go->behaviour->isServer = false;
			}

			go->final_position = go->position;
			go->initial_position = go->position;
			go->final_angle = go->angle;
			go->initial_angle = go->angle;

			bool haveAnimation = false;
			packet >> haveAnimation;

			if (haveAnimation)
			{
				std::string tag;
				packet >> tag;
				go->animation = App->modAnimations->useAnimation(tag.c_str());
			}
			else
			{
				uint32 UID;
				packet >> UID;
				if (go->isPlayer)
				{
					go->texture = App->modResources->playerRobot;
				}
				else
				{
					go->texture = App->modTextures->getTexturebyUID(UID);
				}
			}
		}
		else if (action == ReplicationAction::Update_Position)
		{
			GameObject* go = App->modLinkingContext->getNetworkGameObject(networkId);

			vec2 serverposition;
			float angle;
			packet >> serverposition.x;
			packet >> serverposition.y;
			packet >> angle;
			if (go != nullptr)
			{
				go->newReplicationState(serverposition, angle);

				if (!App->modGameObject->interpolateEntities)
				{
					go->position = serverposition;
					go->angle = angle;
				}
			}
		}
		else if (action == ReplicationAction::Update_Texture)
		{
			GameObject* go = App->modLinkingContext->getNetworkGameObject(networkId);

			int32 UID;
			packet >> UID;
			go->texture = App->modTextures->getTexturebyUID(UID);
			if (go->isPlayer && UID == App->modResources->dead->UID)
			{
				go->texture = App->modResources->playerDead;
			}
			else if (go->isPlayer && UID == App->modResources->robot->UID)
			{
				go->texture = App->modResources->playerRobot;
			}
			packet >> go->size.x;
			packet >> go->size.y;
			packet >> go->order;
		}
		else if (action == ReplicationAction::Update_Animation)
		{
			GameObject* go = App->modLinkingContext->getNetworkGameObject(networkId);
			if (go->animation != nullptr)
			{
				packet >> go->animation->spriteDuration;
			}

		}
		else if (action == ReplicationAction::Destroy)
		{
			GameObject* go = App->modLinkingContext->getNetworkGameObject(networkId);
			if (go)
			{
				App->modLinkingContext->unregisterNetworkGameObject(go);
				Destroy(go);
			}
		}
	}
}
