#include <ai.h>
#include <cstring>

AI_SHADER_NODE_EXPORT_METHODS(mmPoffsetMethods);

namespace
{
	enum mmPoffsetParams { p_color, p_offset, p_space };

	const char* enum_list[] =
	{
		"world",
		"object",
		NULL
	};
};


node_parameters
{
	AiParameterRGB("color", 0.5f, 0.5f, 0.5f);
	AiParameterVec("offset", 0.0f, 0.0f, 0.0f);
	AiParameterEnum("space", 0, enum_list);
}

node_initialize
{
}

node_update
{
}

node_finish
{
}

shader_evaluate
{
	int space = AiShaderEvalParamEnum(p_space);
	AtPoint offset = AiShaderEvalParamVec(p_offset);
	AtColor color;

	AiShaderGlobalsTransformPoint(sg, sg->P, 0);

	switch (space)
	{
	case 0:	// world
		sg->P += offset;
		color = AiShaderEvalParamRGB(p_color);
		sg->P -= offset;
		break;

	case 1:	// object
		sg->Po += offset;
		color = AiShaderEvalParamRGB(p_color);
		sg->Po -= offset;
		break;

	default:
		break;
	}

	sg->out.RGB = color;
}

node_loader
{
	if (i > 0)
	return false;

	node->methods = mmPoffsetMethods;
	node->output_type = AI_TYPE_RGB;
	node->name = "mmPoffset";
	node->node_type = AI_NODE_SHADER;
	strcpy(node->version, AI_VERSION);
	return true;
}