#pragma once
#include "Component.hpp"
#include "Math.hpp"

typedef ObjectID GameObjectID;

template < typename T > class ITransform;
typedef ITransform< void > Transform;

template < typename T >
class ITransform : public IComponent< ITransform< T > >
{
public:

	ITransform()
		: m_GlobalMatrix( Matrix4::Identity )
		, m_LocalMatrix( Matrix4::Identity )
		, m_LocalPosition( Vector3::Zero )
		, m_LocalScale( Vector3::One )
		, m_IsDirty( true )
		, m_Parent( GameObjectID( -1 ) )
	{ }

	inline void SetDirty()
	{
		m_IsDirty = true;
	}

	inline Transform* GetParent()
	{
		return m_Parent == GameObjectID( -1 ) ? nullptr : GetTransform( m_Parent );
	}

	inline const Transform* GetParent() const
	{
		return m_Parent == GameObjectID( -1 ) ? nullptr : GetTransform( m_Parent );
	}

	void SetParent( Transform* a_Parent, bool a_RetainGlobalTransform = true )
	{
		SetParentImpl( a_Parent, a_RetainGlobalTransform );
	}

	inline size_t GetChildCount() const
	{
		return m_Children.size();
	}

	inline Transform* GetChild( size_t a_Index )
	{
		return m_Children[ a_Index ];
	}

	inline void AttachChild( Transform* a_Transform, bool a_RetainGlobalTransform = true )
	{
		if ( !a_Transform )
		{
			return;
		}

		a_Transform->SetParent( this, a_RetainGlobalTransform );
	}

	inline void DetachChild( size_t a_Index, bool a_RetainGlobalTransform = true )
	{
		m_Children[ a_Index ]->SetParentImpl( nullptr, a_RetainGlobalTransform, a_Index );
	}

	inline void DetachChildren( bool a_RetainGlobalTransforms = true )
	{
		for ( size_t i = m_Children.size() - 1; i >= 0; --i )
		{
			DetachChild( i, a_RetainGlobalTransforms );
		}
	}

	inline Vector3 GetLocalPosition() const
	{
		return m_LocalPosition;
	}

	inline float GetLocalPositionX() const
	{
		return m_LocalPosition.x;
	}

	inline float GetLocalPositionY() const
	{
		return m_LocalPosition.y;
	}

	inline float GetLocalPositionZ() const
	{
		return m_LocalPosition.x;
	}

	inline Quaternion GetLocalRotation() const
	{
		return m_LocalRotation;
	}

	inline Vector3 GetLocalScale() const
	{
		return m_LocalScale;
	}

	inline float GetLocalScaleX() const
	{
		return m_LocalScale.x;
	}

	inline float GetLocalScaleY() const
	{
		return m_LocalScale.y;
	}

	inline float GetLocalScaleZ() const
	{
		return m_LocalScale.z;
	}

	inline void SetLocalPosition( const Vector3& a_Position )
	{
		m_LocalPosition = a_Position;
		m_IsDirty = true;
	}

	inline void SetLocalPositionX( float a_X )
	{
		m_LocalPosition.x = a_X;
		m_IsDirty = true;
	}

	inline void SetLocalPositionY( float a_Y )
	{
		m_LocalPosition.y = a_Y;
		m_IsDirty = true;
	}

	inline void SetLocalPositionZ( float a_Z )
	{
		m_LocalPosition.z = a_Z;
		m_IsDirty = true;
	}

	inline void SetLocalRotation( const Quaternion& a_Rotation )
	{
		m_LocalRotation = a_Rotation;
		m_IsDirty = true;
	}

	inline void SetLocalScale( const Vector3& a_Scale )
	{
		m_LocalScale = a_Scale;
		m_IsDirty = true;
	}

	inline void SetLocalScaleX( float a_X )
	{
		m_LocalScale.x = a_X;
		m_IsDirty = true;
	}

	inline void SetLocalScaleY( float a_Y )
	{
		m_LocalScale.y = a_Y;
		m_IsDirty = true;
	}

	inline void SetLocalScaleZ( float a_Z )
	{
		m_LocalScale.z = a_Z;
		m_IsDirty = true;
	}

	inline Vector3 GetGlobalPosition()
	{
		return m_Parent ? Matrix4::ExtractTranslation( m_GlobalMatrix ) : m_LocalPosition;
	}

	inline float GetGlobalPositionX()
	{
		return m_Parent ? Matrix4::ExtractTranslationX( m_GlobalMatrix ) : m_LocalPosition.x;
	}

	inline float GetGlobalPositionY()
	{
		return m_Parent ? Matrix4::ExtractTranslationY( m_GlobalMatrix ) : m_LocalPosition.y;
	}

	inline float GetGlobalPositionZ()
	{
		return m_Parent ? Matrix4::ExtractTranslationZ( m_GlobalMatrix ) : m_LocalPosition.z;
	}

	inline Quaternion GetGlobalRotation()
	{
		return m_Parent ? Matrix4::ExtractRotation( m_GlobalMatrix ) : m_LocalRotation;
	}

	inline Vector3 GetGlobalScale()
	{
		return m_Parent ? Matrix4::ExtractScale( m_GlobalMatrix ) : m_LocalScale;
	}

	inline float GetGlobalScaleX()
	{
		return m_Parent ? Matrix4::ExtractScaleX( m_GlobalMatrix ) : m_LocalScale.x;
	}

	inline float GetGlobalScaleY()
	{
		return m_Parent ? Matrix4::ExtractScaleY( m_GlobalMatrix ) : m_LocalScale.y;
	}

	inline float GetGlobalScaleZ()
	{
		return m_Parent ? Matrix4::ExtractScaleZ( m_GlobalMatrix ) : m_LocalScale.z;
	}

	inline void SetGlobalPosition( const Vector3& a_Position )
	{
		Matrix4::SetTranslation( m_Parent ? m_GlobalMatrix : m_LocalMatrix, a_Position );
		
		if ( !m_Parent )
		{
			m_LocalPosition = a_Position;
		}
		else
		{
			m_LocalMatrix = Math::Multiply( Math::Inverse( m_Parent->m_GlobalMatrix ), m_GlobalMatrix );
			m_LocalPosition = Matrix4::ExtractTranslation( m_LocalMatrix );
		}

		for ( auto* Child : m_Children )
		{
			Child->m_IsDirty = true;
		}
	}

	inline void SetGlobalPositionX( float a_X )
	{
		Matrix4::SetTranslationX( m_Parent ? m_GlobalMatrix : m_LocalMatrix, a_X );
		
		if ( !m_Parent )
		{
			m_LocalPosition.x = a_X;
		}
		else
		{
			m_LocalMatrix = Math::Multiply( Math::Inverse( m_Parent->m_GlobalMatrix ), m_GlobalMatrix );
			m_LocalPosition = Matrix4::ExtractTranslation( m_LocalMatrix );
		}

		for ( auto* Child : m_Children )
		{
			Child->m_IsDirty = true;
		}
	}

	inline void SetGlobalPositionY( float a_Y )
	{
		Matrix4::SetTranslationY( m_Parent ? m_GlobalMatrix : m_LocalMatrix, a_Y );
		
		if ( !m_Parent )
		{
			m_LocalPosition.y = a_Y;
		}
		else
		{
			m_LocalMatrix = Math::Multiply( Math::Inverse( m_Parent->m_GlobalMatrix ), m_GlobalMatrix );
			m_LocalPosition = Matrix4::ExtractTranslation( m_LocalMatrix );
		}

		for ( auto* Child : m_Children )
		{
			Child->m_IsDirty = true;
		}
	}

	inline void SetGlobalPositionZ( float a_Z )
	{
		Matrix4::SetTranslationX( m_Parent ? m_GlobalMatrix : m_LocalMatrix, a_Z );
		
		if ( !m_Parent )
		{
			m_LocalPosition.z = a_Z;
		}
		else
		{
			m_LocalMatrix = Math::Multiply( Math::Inverse( m_Parent->m_GlobalMatrix ), m_GlobalMatrix );
			m_LocalPosition = Matrix4::ExtractTranslation( m_LocalMatrix );
		}

		for ( auto* Child : m_Children )
		{
			Child->m_IsDirty = true;
		}
	}

	inline void SetGlobalRotation( const Quaternion& a_Rotation )
	{
		Matrix4::SetRotation( m_Parent ? m_GlobalMatrix : m_LocalMatrix, a_Rotation );
		
		if ( !m_Parent )
		{
			m_LocalRotation = a_Rotation;
		}
		else
		{
			m_LocalMatrix = Math::Multiply( Math::Inverse( m_Parent->m_GlobalMatrix ), m_GlobalMatrix );
			m_LocalRotation = Matrix4::ExtractRotation( m_LocalMatrix );
		}

		for ( auto* Child : m_Children )
		{
			Child->m_IsDirty = true;
		}
	}

	inline void SetGlobalScale( const Vector3& a_Scale )
	{
		Matrix4::SetScale( m_Parent ? m_GlobalMatrix : m_LocalMatrix, a_Scale );
		
		if ( !m_Parent )
		{
			m_LocalScale = a_Scale;
		}
		else
		{
			m_LocalMatrix = Math::Multiply( Math::Inverse( m_Parent->m_GlobalMatrix ), m_GlobalMatrix );
			m_LocalScale = Matrix4::ExtractScale( m_LocalMatrix );
		}

		for ( auto* Child : m_Children )
		{
			Child->m_IsDirty = true;
		}
	}

	inline void SetGlobalScaleX( float a_X )
	{
		Matrix4::SetScaleX( m_Parent ? m_GlobalMatrix : m_LocalMatrix, a_X );
		
		if ( !m_Parent )
		{
			m_LocalScale.x = a_X;
		}
		else
		{
			m_LocalMatrix = Math::Multiply( Math::Inverse( m_Parent->m_GlobalMatrix ), m_GlobalMatrix );
			m_LocalScale = Matrix4::ExtractScale( m_LocalMatrix );
		}

		for ( auto* Child : m_Children )
		{
			Child->m_IsDirty = true;
		}
	}

	inline void SetGlobalScaleY( float a_Y )
	{
		Matrix4::SetScaleY( m_Parent ? m_GlobalMatrix : m_LocalMatrix, a_Y );
		
		if ( !m_Parent )
		{
			m_LocalScale.y = a_Y;
		}
		else
		{
			m_LocalMatrix = Math::Multiply( Math::Inverse( m_Parent->m_GlobalMatrix ), m_GlobalMatrix );
			m_LocalScale = Matrix4::ExtractScale( m_LocalMatrix );
		}

		for ( auto* Child : m_Children )
		{
			Child->m_IsDirty = true;
		}
	}

	inline void SetGlobalScaleZ( float a_Z )
	{
		Matrix4::SetScaleZ( m_Parent ? m_GlobalMatrix : m_LocalMatrix, a_Z );
		
		if ( !m_Parent )
		{
			m_LocalScale.z = a_Z;
		}
		else
		{
			m_LocalMatrix = Math::Multiply( Math::Inverse( m_Parent->m_GlobalMatrix ), m_GlobalMatrix );
			m_LocalScale = Matrix4::ExtractScale( m_LocalMatrix );
		}

		for ( auto* Child : m_Children )
		{
			Child->m_IsDirty = true;
		}
	}

	inline Vector3 GetLocalForward() const
	{
		return Math::Normalize( m_LocalMatrix.c2.ToVector3() );
	}

	inline Vector3 GetLocalBackward() const
	{
		return -Math::Normalize( m_LocalMatrix.c2.ToVector3() );
	}

	inline Vector3 GetLocalRight() const
	{
		return Math::Normalize( m_LocalMatrix.c0.ToVector3() );
	}

	inline Vector3 GetLocalLeft() const
	{
		return -Math::Normalize( m_LocalMatrix.c0.ToVector3() );
	}

	inline Vector3 GetLocalUp() const
	{
		return Math::Normalize( m_LocalMatrix.c1.ToVector3() );
	}

	inline Vector3 GetLocalDown() const
	{
		return -Math::Normalize( m_LocalMatrix.c1.ToVector3() );
	}

	inline Vector3 GetGlobalForward() const
	{
		return Math::Normalize( ( m_Parent ? m_GlobalMatrix : m_LocalMatrix ).c2.ToVector3() );
	}

	inline Vector3 GetGlobalBackward() const
	{
		return -Math::Normalize( ( m_Parent ? m_GlobalMatrix : m_LocalMatrix ).c2.ToVector3() );
	}

	inline Vector3 GetGlobalRight() const
	{
		return Math::Normalize( ( m_Parent ? m_GlobalMatrix : m_LocalMatrix ).c0.ToVector3() );
	}

	inline Vector3 GetGlobalLeft() const
	{
		return -Math::Normalize( ( m_Parent ? m_GlobalMatrix : m_LocalMatrix ).c0.ToVector3() );
	}

	inline Vector3 GetGlobalUp() const
	{
		return Math::Normalize( ( m_Parent ? m_GlobalMatrix : m_LocalMatrix ).c1.ToVector3() );
	}

	inline Vector3 GetGlobalDown() const
	{
		return -Math::Normalize( ( m_Parent ? m_GlobalMatrix : m_LocalMatrix ).c1.ToVector3() );
	}

	void SetLocalForward( const Vector3& a_Forward )
	{

	}

	void SetLocalBackward( const Vector3& a_Backward )
	{

	}

	void SetLocalRight( const Vector3& a_Right )
	{

	}

	void SetLocalLeft( const Vector3& a_Left )
	{

	}

	void SetLocalUp( const Vector3& a_Up )
	{

	}

	void SetLocalDown( const Vector3& a_Down )
	{

	}

	void SetGlobalForward( const Vector3& a_Forward )
	{

	}

	void SetGlobalBackward( const Vector3& a_Backward )
	{

	}

	void SetGlobalRight( const Vector3& a_Right )
	{

	}

	void SetGlobalLeft( const Vector3& a_Left )
	{

	}

	void SetGlobalUp( const Vector3& a_Up )
	{

	}

	void SetGlobalDown( const Vector3& a_Down )
	{

	}

	void TranslateLocal( const Vector3& a_Translation )
	{

	}

	void TranslateLocalX( float a_X )
	{

	}

	void TranslateLocalY( float a_Y )
	{

	}

	void TranslateLocalZ( float a_Z )
	{

	}

	void TranslateGlobal( const Vector3& a_Translation )
	{

	}

	void TranslateGlobalX( float a_X )
	{

	}

	void TranslateGlobalY( float a_Y )
	{

	}

	void TranslateGlobalZ( float a_Z )
	{

	}

	void RotateLocal( const Quaternion& a_Rotation )
	{

	}

	void RotateGlobal( const Quaternion& a_Rotation )
	{

	}

	void ScaleLocal( const Vector3& a_Scale )
	{

	}

	void ScaleLocalX( float a_X )
	{

	}

	void ScaleLocalY( float a_Y )
	{

	}

	void ScaleLocalZ( float a_Z )
	{

	}

	void ScaleGlobal( const Vector3& a_Scale )
	{

	}

	void ScaleGlobalX( float a_X )
	{

	}

	void ScaleGlobalY( float a_Y )
	{

	}

	void ScaleGlobalZ( float a_Z )
	{

	}

	inline const Matrix4& GetGlobalMatrix() const
	{
		return m_Parent ? m_GlobalMatrix : m_LocalMatrix;
	}

	inline const Matrix4& GetLocalMatrix() const
	{
		return m_LocalMatrix;
	}

//private:

	inline void SetParentImpl( Transform* a_Transform, bool a_RetainGlobalTransform, size_t a_ChildIndex = -1 )
	{
		GameObjectID ThisID = ComponentBase::GetGameObject().GetObjectID();

		// unset parent
		if ( m_Parent != GameObjectID( -1 ) )
		{
			m_LocalMatrix = m_GlobalMatrix;
			auto Where = a_ChildIndex == -1 ? std::find( m_Parent->m_Children.begin(), m_Parent->m_Children.end(), ThisID ) : m_Parent->m_Children.begin() + a_ChildIndex;
			m_Parent->m_Children.erase( Where );
		}

		// set parent
		if ( a_Transform )
		{
			m_LocalMatrix = Math::Multiply( Math::Inverse( a_Transform->m_GlobalMatrix ), m_LocalMatrix );
			a_Transform->m_Children.push_back( ThisID );
		}

		m_Parent = a_Transform->GetGameObject().GetObjectID();
	}

	void UpdateTransform()
	{
		if ( m_IsDirty )
		{
			m_LocalMatrix = Matrix4::CreateTransform( m_LocalPosition, m_LocalRotation, m_LocalScale );
			m_IsDirty = false;
		}

		if ( m_Parent != GameObjectID( -1 ) )
		{
			m_GlobalMatrix = Math::Multiply( GetParent()->GetGlobalMatrix(), m_LocalMatrix );
		}

		for ( auto Begin = m_Children.begin(), End = m_Children.end(); Begin != End; ++Begin )
		{
			( *Begin )->UpdateTransform();
		}
	}

	Matrix4      m_GlobalMatrix;
	Matrix4      m_LocalMatrix;
	Vector3      m_LocalPosition;
	Quaternion   m_LocalRotation;
	Vector3      m_LocalScale;
	bool         m_IsDirty;
	GameObjectID m_Parent;
	std::vector< GameObjectID > m_Children;
};

Transform* GetTransform( GameObjectID a_GameObjectID );