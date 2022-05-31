#pragma once
#include "ECS.hpp"
#include "Transform.hpp"
#include "Alias.hpp"

typedef uint32_t GameObjectID;
typedef uint32_t Hash;
struct Name;

class GameObject
{
public:

	inline bool IsValid() const
	{
		return m_ID == static_cast< GameObjectID >( -1 );
	}

	template < typename T >
	inline T* AddComponent()
	{
		return ECS::AddComponent< T >( m_ID );
	}

	template < typename T >
	inline T* GetComponent()
	{
		return ECS::GetComponent< T >( m_ID );
	}

	template < typename T >
	inline const T* GetComponent() const
	{
		return ECS::GetComponentConst< T >( m_ID );
	}

	inline Alias* GetAlias()
	{
		return ECS::GetExactComponent< Alias >( m_ID );
	}

	inline const Alias* GetAlias() const
	{
		return ECS::GetExactComponent< const Alias >( m_ID );
	}

	inline Transform* GetTransform()
	{
		return ECS::GetExactComponent< Transform >( m_ID );
	}

	inline const Transform* GetTransform() const
	{
		return ECS::GetExactComponent< const Transform >( m_ID );
	}

	template < typename T >
	inline bool DestroyComponent()
	{
		return ECS::DestroyComponent< T >();
	}

	inline GameObjectID GetID() const
	{
		return m_ID;
	}

	inline static GameObject FindByID( GameObjectID a_GameObjectID )
	{
		return *reinterpret_cast< GameObject* >( &a_GameObjectID );
	}

	inline static GameObject FindByName( Hash a_Name )
	{
		return GameObject::FindByID( Alias::FindByName( a_Name ) );
	}

	inline static GameObject Instantiate()
	{
		return FindByID( ECS::Instantiate() );
	}

	inline static GameObject Instantiate( GameObject a_Parent )
	{
		return FindByID( ECS::Instantiate( reinterpret_cast< GameObjectID&& >( a_Parent ) ) );
	}

	inline static GameObject Instantiate( const Name& a_Name )
	{
		return FindByID( ECS::Instantiate( a_Name ) );
	}

	inline static GameObject Instantiate( const Name& a_Name, GameObject a_Parent )
	{
		return FindByID( ECS::Instantiate( a_Name, reinterpret_cast< GameObjectID&& >( a_Parent ) ) );
	}

	inline static GameObject Destroy( GameObject a_GameObject )
	{
		// implementation
	}

	operator GameObjectID()
	{
		return m_ID;
	}

	operator GameObjectID const() const
	{
		return m_ID;
	}

private:

	GameObjectID m_ID;
};