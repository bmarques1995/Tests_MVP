#include "Shader.hpp"
#include "Application.hpp"
#ifdef RENDER_USES_WINDOWS
#include "D3D12Shader.hpp"
#include "D3D12Context.hpp"
#endif

SampleRender::Shader* SampleRender::Shader::Instantiate(const std::shared_ptr<GraphicsContext>* context, std::string json_basepath, BufferLayout layout)
{
	GraphicsAPI api = Application::GetInstance()->GetCurrentAPI();
	std::stringstream controller_path;
	controller_path << json_basepath;
	switch (api)
	{
#ifdef RENDER_USES_WINDOWS
	case SampleRender::D3D12:
	{
		controller_path << ".d3d12.json";
		std::string json_controller_path = controller_path.str();
		return new D3D12Shader((const std::shared_ptr<D3D12Context>*)(context), json_controller_path, layout);
	}
#endif
	default:
		break;
	}
	return nullptr;
}
