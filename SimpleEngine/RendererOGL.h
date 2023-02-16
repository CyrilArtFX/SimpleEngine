#pragma once
#include "IRenderer.h"
#include "VertexArray.h"
#include "Vector2.h"
#include "Shader.h"
#include "DirectionalLight.h"
#include <vector>

class RendererOGL : public IRenderer
{
public:
	RendererOGL();
	virtual ~RendererOGL();
	RendererOGL(const RendererOGL&) = delete;
	RendererOGL& operator=(const RendererOGL&) = delete;

	bool initialize(Window& window);
	void beginDraw();
	void draw();
	void endDraw();

	void addSprite(class SpriteComponent* sprite);
	void removeSprite(class SpriteComponent* sprite);
	void drawSprite(const Actor& actor, const class Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip) const;

	void addMesh(class MeshComponent* mesh);
	void removeMesh(class MeshComponent* mesh);

	DirectionalLight& getDirectionalLight() { return dirLight; }

	void setViewMatrix(const Matrix4& viewP);
	void setLightUniforms(Shader& shader);
	void setAmbientLight(const Vector3& ambientP);

	void close();
	IRenderer::Type type() { return Type::OGL; }

private:
	void drawSprites();
	void drawMeshes();

	Window* window;
	SDL_GLContext context;
	VertexArray* spriteVertexArray;
	Matrix4 spriteViewProj;
	Matrix4 view;
	Matrix4 projection;

	Vector3 ambientLight;
	DirectionalLight dirLight;

	std::vector<class SpriteComponent*> sprites;
	std::vector<class MeshComponent*> meshes;
};

