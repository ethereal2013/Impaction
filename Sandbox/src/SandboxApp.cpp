#include <Impaction.h>
#include "Platform/OpenGL/OpenGLShader.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public impct::Layer
{
public:
	ExampleLayer()
		: impct::Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_SquarePosition(0.0f)
	{
		m_VertexArray.reset(impct::VertexArray::Create());

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

		m_SquareVA.reset(impct::VertexArray::Create());

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

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader.reset(impct::Shader::Create(vertexSrc, fragmentSrc));

		std::string FlatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string FlatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader.reset(impct::Shader::Create(FlatColorShaderVertexSrc, FlatColorShaderFragmentSrc));

		std::string textureShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TextCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TextCoord;

			void main()
			{
				v_TextCoord = a_TextCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string textureShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec2 v_TextCoord;
			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TextCoord);
			}
		)";

		m_TextureShader.reset(impct::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));
		m_Texture = impct::Texture2D::Create("assets/textures/checkerboard-512x512.png");

		std::dynamic_pointer_cast<impct::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<impct::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(impct::Timestep ts) override
	{
		IMPCT_TRACE("Delta Time = {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

		//------------------------------- Camera Movement ----------------------------------

		glm::vec2 cameraMovement(0.0f);

		if (impct::Input::IsKeyPressed(IMPCT_KEY_LEFT))	       cameraMovement.x -= 1.0f;
		else if (impct::Input::IsKeyPressed(IMPCT_KEY_RIGHT))  cameraMovement.x += 1.0f;

		if (impct::Input::IsKeyPressed(IMPCT_KEY_UP))	       cameraMovement.y += 1.0f;
		else if (impct::Input::IsKeyPressed(IMPCT_KEY_DOWN))   cameraMovement.y -= 1.0f;

		float cameraRotation = glm::radians(m_CameraRotation);

		//World (x, y) is NOT camera rotated (x, y).
		glm::vec2 rotatedMovement(
			cameraMovement.x * cos(cameraRotation) - cameraMovement.y * sin(cameraRotation),
			cameraMovement.x * sin(cameraRotation) + cameraMovement.y * cos(cameraRotation)
		);

		m_CameraPosition.x += rotatedMovement.x * m_CameraMoveSpeed * ts;
		m_CameraPosition.y += rotatedMovement.y * m_CameraMoveSpeed * ts;

		if (impct::Input::IsKeyPressed(IMPCT_KEY_A)) m_CameraRotation += m_CameraRotationSpeed * ts;
		if (impct::Input::IsKeyPressed(IMPCT_KEY_D)) m_CameraRotation -= m_CameraRotationSpeed * ts;

		//----------------------------------------------------------------------------------

		//------------------------------- Square Movement ----------------------------------

		if (impct::Input::IsKeyPressed(IMPCT_KEY_J))	  m_SquarePosition.x -= m_SquareMoveSpeed * ts;
		else if (impct::Input::IsKeyPressed(IMPCT_KEY_L)) m_SquarePosition.x += m_SquareMoveSpeed * ts;

		if (impct::Input::IsKeyPressed(IMPCT_KEY_I))	  m_SquarePosition.y += m_SquareMoveSpeed * ts;
		else if (impct::Input::IsKeyPressed(IMPCT_KEY_K)) m_SquarePosition.y -= m_SquareMoveSpeed * ts;

		//----------------------------------------------------------------------------------

		impct::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			impct::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		impct::Renderer::BeginScene(m_Camera);
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

			//impct::Renderer::Submit(m_Shader, m_VertexArray);
			m_Texture->Bind();
			impct::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		}
		impct::Renderer::EndScene();
	}

	void OnEvent(impct::Event& event) override
	{
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
	impct::Ref<impct::VertexArray> m_VertexArray;
	impct::Ref<impct::Shader> m_Shader;

	impct::Ref<impct::Shader> m_FlatColorShader, m_TextureShader;
	impct::Ref<impct::VertexArray> m_SquareVA;

	impct::Ref<impct::Texture2D> m_Texture;

	impct::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f, m_CameraRotation = 0.0f, m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquarePosition;
	float m_SquareMoveSpeed = 1.0f;

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