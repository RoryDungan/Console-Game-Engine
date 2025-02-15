#include "Shader.hpp"
#include "Light.hpp"


Shader Shader::Default;
Shader Shader::Diffuse = Shader( "Diffuse"_N, "Vertex_Texel", "Fragment_Diffuse" );
Shader Shader::Specular = Shader( "Specular"_N, "Vertex_Texel", "Fragment_Specular" );
Shader Shader::Normal = Shader( "Normal"_N, "Vertex_Texel", "Fragment_Normal" );
Shader Shader::Phong;//    = Shader( "Phong"_N,    "Vertex_Texel", "Phong_Fragment"    );
Shader Shader::UnlitFlatColour = Shader( "UnlitFlatColour"_N, "Vertex_Default", "Fragment_Unlit_Flat_Colour" );
Shader Shader::LitFlatColour = Shader( "LitFlatColour"_N, "Vertex_Lit_Flat_Colour", "Fragment_Lit_Flat_Colour" );

// Vertex Default
DefineShader( Vertex_Default )
{
	Uniform( Matrix4, u_PVM );
	Attribute( 0, Vector3, a_Position );
	Rendering::Position = Math::Multiply( u_PVM, Vector4( a_Position, 1.0f ) );
}

// Vertex Texel Only
DefineShader( Vertex_Texel )
{
	Uniform( Matrix4, u_PVM );
	Attribute( 0, Vector3, a_Position );
	Attribute( 1, Vector2, a_Texel );
	Varying_Out( Vector2, Texel );

	Rendering::Position = Math::Multiply( u_PVM, Vector4( a_Position, 1.0f ) );
	Texel = a_Texel;
}

// Fragment Default
DefineShader( Fragment_Default )
{
	Rendering::FragColour = Colour::PINK;
}

// Fragment Diffuse
DefineShader( Fragment_Diffuse )
{
	Uniform( Sampler2D, texture_diffuse );
	Varying_In( Vector2, Texel );

	Rendering::FragColour = Rendering::Sample( texture_diffuse, Texel );
}

// Fragment Specular
DefineShader( Fragment_Specular )
{
	Uniform( Sampler2D, texture_specular );
	Varying_In( Vector2, Texel );

	Rendering::FragColour = Rendering::Sample( texture_specular, Texel );
}

// Fragment Normal
DefineShader( Fragment_Normal )
{
	Uniform( Sampler2D, texture_normal );
	Varying_In( Vector2, Texel );

	Rendering::FragColour = Rendering::Sample( texture_normal, Texel );
}

// Vertex Unlit Flat Colour
//DefineShader( Vertex_Unlit_Flat_Colour )
//{
//
//}

// Fragment Unlit Flat Colour
DefineShader( Fragment_Unlit_Flat_Colour )
{
	Uniform( Vector4, diffuse_colour );

	Rendering::FragColour = diffuse_colour;
}

// Vertex Lit Flat Colour
DefineShader( Vertex_Lit_Flat_Colour )
{
	Uniform( Matrix4, u_PVM );
	Uniform( Matrix4, u_Model );
	Attribute( 0, Vector3, a_Position );
	Attribute( 3, Vector3, a_Normal );
	Varying_Out( Vector3, Normal );

	Normal = Math::Multiply( u_Model, Vector4( a_Normal ) );
	Rendering::Position = Math::Multiply( u_PVM, Vector4( a_Position, 1.0f ) );
}

// Fragment Lit Flat Colour
DefineShader( Fragment_Lit_Flat_Colour )
{
	Uniform( Vector4, diffuse_colour );
	Uniform( Vector3, u_SunLight );
	Varying_In( Vector3, Normal );

	float Intensity = Math::Clamp( -Math::Dot( u_SunLight, Normal ), 0.0f, 1.0f );
	Rendering::FragColour.x = Intensity * diffuse_colour.x;
	Rendering::FragColour.y = Intensity * diffuse_colour.y;
	Rendering::FragColour.z = Intensity * diffuse_colour.z;
	Rendering::FragColour.w = diffuse_colour.w;
}