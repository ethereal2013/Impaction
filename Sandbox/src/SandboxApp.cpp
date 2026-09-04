#include <Impaction.h>
#include "Platform/OpenGL/OpenGLShader.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public impct::Layer
{
public:
	ExampleLayer()
		: impct::Layer("Example"), m_CameraController(1280.0f / 720.0f, true)
	{
		m_VertexArray = impct::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};

		impct::Ref<impct::VertexBuffer> vertexBuffer(impct::VertexBuffer::Create(vertices, sizeof(vertices)));

		impct::BufferLayout layout = {
			{ impct::ShaderDataType::Float3, "a_Position" },
			{ impct::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		impct::Ref<impct::IndexBuffer> indexBuffer(impct::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);
	

		m_SquareVA = impct::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f,  0.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.0f,  1.0f,  1.0f,
			-0.5f,  0.5f,  0.0f,  0.0f,  1.0f
		};

		impct::Ref<impct::VertexBuffer> squareVB(impct::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ impct::ShaderDataType::Float3, "a_Position" },
			{ impct::ShaderDataType::Float2, "a_TextCoord" }
		} );
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		impct::Ref<impct::IndexBuffer> squareIB(impct::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		m_SquareVA->SetIndexBuffer(squareIB);

		//Shaders
		m_Shader = impct::Shader::Create("assets/shaders/TriangleShader.glsl");
		m_FlatColorShader = impct::Shader::Create("assets/shaders/FlatColor.glsl");
		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		//Textures
		m_Texture = impct::Texture2D::Create("assets/textures/chess.png");
		m_LogoTexture = impct::Texture2D::Create("assets/textures/logo.png");

		std::dynamic_pointer_cast<impct::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<impct::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(impct::Timestep ts) override
	{
		m_CameraController.OnUpdate(ts);

		impct::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			impct::RenderCommand::Clear();

		impct::Renderer::BeginScene(m_CameraController.GetCamera());
		{
			glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

			glm::vec4 redColor  = { 0.8f, 0.2f, 0.3f, 1.0f };
			glm::vec4 blueColor = { 0.2f, 0.3f, 0.8f, 1.0f };

			std::dynamic_pointer_cast<impct::OpenGLShader>(m_FlatColorShader)->Bind();
			std::dynamic_pointer_cast<impct::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

			for (int y = 0; y < 20; y++)
			{
				for (int x = 0; x < 20; x++)
				{
					glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
					impct::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
				}
			}

			//Triangle
			/*{
				impct::Renderer::Submit(m_Shader, m_VertexArray);
			}*/

			
			auto textureShader = m_ShaderLibrary.Get("Texture");

			m_Texture->Bind();
			impct::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

			m_LogoTexture->Bind();
			impct::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		}
		impct::Renderer::EndScene();
	}

	void OnEvent(impct::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		{
			ImGui::ColorEdit3("SquareColor", glm::value_ptr(m_SquareColor));
		}
		ImGui::End();
	}

private:
	//NOTE: The implementation of ShaderLibrary will be part of the renderer.
	//This is temporary
	impct::ShaderLibrary m_ShaderLibrary;

	impct::Ref<impct::VertexArray> m_VertexArray;
	impct::Ref<impct::Shader> m_Shader;

	impct::Ref<impct::Shader> m_FlatColorShader;
	impct::Ref<impct::VertexArray> m_SquareVA;

	impct::Ref<impct::Texture2D> m_Texture, m_LogoTexture;

	impct::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public impct::Application
{
public:
	Sandbox()
	{ 
		PushLayer(new ExampleLayer()); 
	}

	~Sandbox() override {}
};

//Runs in the main function
impct::Application* impct::CreateApplication()
{
	return new Sandbox();
}