#pragma once

#include <rapidjson/document.h>
#include <string>
#include "Math/Vector2.h"
#include "Renderer/Color.h"

#define READ_DATA(value, data) Json::Read(value, #data, data, false)
#define READ_DATA_REQUIRED(value, data) Json::Read(value, #data, data, true)
#define READ_DATA_NAME(value, name, data) Json::Read(value, name, data)

#define HAS_DATA(value, data) value.HasMember(#data)
#define GET_DATA(value, data) value[#data]


namespace Json {
	bool Load(const std::string& filename, rapidjson::Document& document);
	bool Read(const rapidjson::Value& value, const std::string& name, int& data, bool isRequired);
	bool Read(const rapidjson::Value& value, const std::string& name, float& data, bool isRequired);
	bool Read(const rapidjson::Value& value, const std::string& name, bool& data, bool isRequired);
	bool Read(const rapidjson::Value& value, const std::string& name, std::string& data, bool isRequired);
	bool Read(const rapidjson::Value& value, const std::string& name, Vector2& data, bool isRequired);
	bool Read(const rapidjson::Value& value, const std::string& name, Color& data, bool isRequired );
}
using json_t = rapidjson::Value;
typedef rapidjson::Value json_t;