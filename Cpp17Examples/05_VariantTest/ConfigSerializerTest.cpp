#include "pch.h"
#include "gtest/gtest.h"
#include "..\05_Variant\Config_Serializer.h"

using namespace ConfigSerializerSample;

TEST(ConfigSerializerTest, SerializeBasicTypes)
{
	ConfigSerializer::ConfigMap cfg;
	cfg["threads"] = 4;
	cfg["pi"] = 3.14;
	cfg["mode"] = std::string{ "debug" };
	cfg["feature"] = true;

	auto json = ConfigSerializer::serialize(cfg);

	EXPECT_NE(json.find("\"threads\":4"), std::string::npos);
	EXPECT_NE(json.find("\"pi\":3.14"), std::string::npos);
	EXPECT_NE(json.find("\"mode\":\"debug\""), std::string::npos);
	EXPECT_NE(json.find("\"feature\":true"), std::string::npos);
}

TEST(ConfigSerializerTest, DeserializeAndCheckValues)
{
	std::string json = R"({"threads":8,"pi":2.71,"mode":"release","feature":false})";
	ConfigSerializer::ConfigMap cfg = ConfigSerializer::deserialize(json);

	EXPECT_EQ(std::get<int>(cfg["threads"]), 8);
	EXPECT_DOUBLE_EQ(std::get<double>(cfg["pi"]), 2.71);
	EXPECT_EQ(std::get<std::string>(cfg["mode"]), "release");
	EXPECT_EQ(std::get<bool>(cfg["feature"]), false);


}

class ConfigManagerTest : public ::testing::Test
{
	protected:
	void SetUp() override
	{
		config.set("database.host", std::string("localhost"));
		config.set("database.port", 3306);
		config.set("database.enabled", true);
		config.set("theme", std::string("dark"));  // section ‚È‚µ
		config.set("timeout", 10.5);               // section ‚È‚µ
		config.set("misc.stringBoolTrue", std::string("true"));
		config.set("misc.stringBoolFalse", std::string("0"));
		config.set("misc.invalidInt", std::string("not_a_number"));
	}
	ConfigManager config;
};

TEST_F(ConfigManagerTest, GetOrDefaultWorks)
{
    EXPECT_EQ(config.getStringOrDefault("database.host", "default"), "localhost");
    EXPECT_EQ(config.getIntOrDefault("database.port", 1234), 3306);
    EXPECT_TRUE(config.getBoolOrDefault("database.enabled", false));
    EXPECT_DOUBLE_EQ(config.getDoubleOrDefault("timeout", 0.0), 10.5);

    EXPECT_EQ(config.getStringOrDefault("nonexistent", "def"), "def");
    EXPECT_EQ(config.getIntOrDefault("nonexistentInt", 42), 42);
    EXPECT_FALSE(config.getBoolOrDefault("nonexistentBool", false));
}

TEST_F(ConfigManagerTest, ContainsDetectsKeys)
{
    EXPECT_TRUE(config.contains("host"));
    EXPECT_TRUE(config.contains("port"));
    EXPECT_TRUE(config.contains("theme"));
    EXPECT_FALSE(config.contains("nonexistent"));
}

TEST_F(ConfigManagerTest, GetKeysListsPlainKeys)
{
    auto keys = config.getKeys();
    EXPECT_NE(std::find(keys.begin(), keys.end(), "host"), keys.end());
    EXPECT_NE(std::find(keys.begin(), keys.end(), "port"), keys.end());
    EXPECT_NE(std::find(keys.begin(), keys.end(), "theme"), keys.end());
    EXPECT_NE(std::find(keys.begin(), keys.end(), "timeout"), keys.end());
}

TEST_F(ConfigManagerTest, GetSectionMapStringConvertsValues)
{
    auto dbMap = config.getSectionMap<std::string>("database");
    EXPECT_EQ(dbMap.size(), 3);
    EXPECT_EQ(dbMap.at("host"), "localhost");
    EXPECT_EQ(dbMap.at("port"), "3306");
    EXPECT_EQ(dbMap.at("enabled"), "true");

    auto themeMap = config.getSectionMap<std::string>("theme");
    EXPECT_TRUE(themeMap.empty());
}

TEST_F(ConfigManagerTest, GetSectionMapConfigValuePreservesTypes)
{
    auto dbMap = config.getSectionMap<ConfigValue>("database");
    EXPECT_EQ(dbMap.size(), 3);

    auto host = std::get_if<std::string>(&dbMap.at("host"));
    EXPECT_TRUE(host && *host == "localhost");

    auto port = std::get_if<int>(&dbMap.at("port"));
    EXPECT_TRUE(port && *port == 3306);

    auto enabled = std::get_if<bool>(&dbMap.at("enabled"));
    EXPECT_TRUE(enabled && *enabled);
}

TEST_F(ConfigManagerTest, ConversionWorks)
{
    EXPECT_TRUE(config.getBoolOrDefault("misc.stringBoolTrue", false));
    EXPECT_FALSE(config.getBoolOrDefault("misc.stringBoolFalse", true));

    EXPECT_DOUBLE_EQ(config.getDoubleOrDefault("database.port", 0.0), 3306.0);

    EXPECT_EQ(config.getIntOrDefault("timeout", 0), 10);

    EXPECT_EQ(config.getStringOrDefault("database.enabled", "no"), "true");
}

TEST_F(ConfigManagerTest, ConversionFailsGracefully)
{
    auto badInt = config.get<int>("misc.invalidInt");
    EXPECT_FALSE(badInt.has_value());

    config.set("misc.invalidBool", std::string("maybe"));
    auto badBool = config.get<bool>("misc.invalidBool");
    EXPECT_FALSE(badBool.has_value());
}

TEST_F(ConfigManagerTest, EmptySectionReturnsEmptyMap)
{
    auto emptyMap = config.getSectionMap<std::string>("nosuchsection");
    EXPECT_TRUE(emptyMap.empty());
}

TEST_F(ConfigManagerTest, PlainKeysBehaveCorrectly)
{
    EXPECT_EQ(config.getStringOrDefault("theme", "light"), "dark");
    EXPECT_DOUBLE_EQ(config.getDoubleOrDefault("timeout", 0.0), 10.5);

    auto sectionMap = config.getSectionMap<std::string>("timeout");
    EXPECT_TRUE(sectionMap.empty());
}