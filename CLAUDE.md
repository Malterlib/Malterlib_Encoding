# CLAUDE.md - Encoding Module

This file provides guidance to Claude Code (claude.ai/code) when working with the Encoding module in Malterlib.

## Module Overview

The Encoding module provides comprehensive text encoding and data serialization functionality, focusing heavily on JSON processing with additional support for Base64, Bin128, and enhanced JSON formats. The module is designed for high performance with multiple JSON implementations for different use cases.

## Module Location

- **Main Directory**: `Malterlib/Encoding/`
- **Include Path**: `Include/Mib/Encoding/`
- **Source Files**: `Source/Malterlib_Encoding_*.cpp/.h/.hpp`
- **Tests**: `Test/Test_Malterlib_Encoding_*.cpp`

## Core Components

### 1. Base64 Encoding (`Base64`)
Provides Base64 encoding/decoding functionality for strings and binary data.

**Key Classes/Functions**:
- `TCBinaryStream_Base64` - Stream-based Base64 encoding/decoding
- `fg_Base64Encode()` - Encode strings or byte vectors to Base64
- `fg_Base64Decode()` - Decode Base64 strings to original format

**Usage Example**:
```cpp
NStr::CStr EncodedText = fg_Base64Encode("Hello World");
NStr::CStr DecodedText = fg_Base64Decode(EncodedText);

// Binary data encoding
NContainer::CByteVector BinaryData;
NStr::CStr EncodedBinary = fg_Base64Encode(BinaryData);
```

### 2. Bin128 Encoding (`Bin128`)
Handles 128-bit binary value encoding and manipulation.

**Key Classes**:
- Binary 128-bit value handling and string conversion

### 3. JSON Processing (`Json`)
Comprehensive JSON support with two main variants: Ordered and Sorted.

**Main Classes**:
- `CJsonOrdered` - Preserves insertion order of object keys
- `CJsonSorted` - Automatically sorts object keys lexicographically
- `TCJsonValue` - Template base for JSON values
- `TCJsonObject` - JSON object representation

**JSON Types** (`EJsonType`):
- `EJsonType_Invalid` - Invalid/uninitialized value
- `EJsonType_Null` - null value
- `EJsonType_String` - String value
- `EJsonType_Integer` - Integer value (int64)
- `EJsonType_Float` - Floating point value (fp64)
- `EJsonType_Boolean` - Boolean value
- `EJsonType_Object` - Object/dictionary
- `EJsonType_Array` - Array/list

**Common Operations**:
```cpp
// Creating JSON objects
CJsonOrdered Json(EJsonType_Object);
Json["Key"] = "Value";
Json["Number"] = 42;
Json["Float"] = 3.14;
Json["Boolean"] = true;
Json["Null"] = nullptr;

// Arrays
auto &Array = Json["Array"];
Array.f_Insert(25);
Array.f_Insert("Text");
Array.f_Insert(true);

// Nested objects
auto &NestedObject = Json["Object"];
NestedObject["NestedKey"] = "NestedValue";

// Parsing from string
CJsonOrdered ParsedJson = CJsonOrdered::fs_FromString(JsonString);

// Converting to string
NStr::CStr JsonString = fg_JsonGenerate(Json);
```

### 4. Enhanced JSON (`EJson`)
Extended JSON format supporting additional data types beyond standard JSON.

**Additional Types** (`EEJsonType`):
- All standard JSON types plus:
- `EEJsonType_Date` - Date/time values
- `EEJsonType_Binary` - Binary data
- `EEJsonType_UserType` - Custom user-defined types

**Key Classes**:
- `CEJsonOrdered` - Enhanced JSON with ordered keys
- `CEJsonSorted` - Enhanced JSON with sorted keys
- `CEJsonUserTypeOrdered/Sorted` - User-defined type containers

**Usage Example**:
```cpp
CEJsonOrdered EJson;
EJson["Date"] = NTime::CTime::fs_Now();
EJson["Binary"] = NContainer::CByteVector{0x01, 0x02, 0x03};
EJson["Custom"] = fg_UserTypeOrdered("MyType", CJsonOrdered{{"data", "value"}});
```

### 5. JSON Shortcuts (`JsonShortcuts`)
Provides convenient literal operators for JSON construction.

**Operators**:
- `"key"_j` - Creates a JSON key
- `_j[]` - Creates an empty JSON array
- `_j= {}` - Creates a JSON object
- `"key"_` - Creates a EJSON key
- `_[]` - Creates an empty EJSON array
- `_= {}` - Creates a EJSON object

**Usage Example**:
```cpp
CJsonSorted Json =
{
	"Name"_j= "John"
	, "Age"_j= 30
	, "Address"_j=
	{
		"Street"_j= "123 Main St"
		, "City"_j= "New York"
	}
	, "Hobbies"_j= _j["Reading", "Gaming", "Coding"]
};

CEJsonSorted EJson =
{
	"Name"_= "John"
	, "Age"_= 30
	, "Address"_=
	{
		"Street"_= "123 Main St"
		, "City"_= "New York"
	}
	, "Hobbies"_= _["Reading", "Gaming", "Coding"]
};
```

### 6. Simple JSON Database (`SimpleJsonDatabase`)
Provides a simple file-based JSON database with async load/save operations.

**Key Features**:
- Async file operations using futures
- Thread-safe write operations with sequencer
- Automatic JSON serialization/deserialization

**Usage Example**:
```cpp
CSimpleJsonDatabase Database("data.json");
co_await Database.f_Load();
// Modify Database.m_Data
co_await Database.f_Save();
```

### 7. ToJson Conversion (`ToJson`)
Utilities for converting various types to JSON representation.

## External Dependencies

The module integrates with several external JSON libraries for comparison and testing:
- **rapidjson** - Tencent's RapidJSON library
- **nlohmann/json** - Popular modern C++ JSON library
- **daw_json_link** - High-performance JSON library
- **header_libraries** - Supporting header libraries
- **utf_range** - UTF string range utilities

These are only included when `MalterlibEnableThirdPartyComparisonTests` is enabled.

## Code Patterns and Conventions

### Naming Conventions
Following Malterlib standards:
- Functions: `f_` prefix for members, `fg_` for global functions
- Member variables: `m_` prefix
- Private/protected members: `mp_` prefix
- Template parameters: `t_` prefix
- Constants: `mc_` prefix for member constants, `gc_` for global

### JSON Value Access Patterns
```cpp
// Type checking
if (Json.f_IsObject())
{
	// Safe member access
	if (CJsonOrdered const *pValue = Json.f_GetMember("Key"))
	{
		// Use pValue
	}

	// Direct access (creates if missing)
	Json["Key"] = "Value";

	// Get with default
	int64 Value = Json.f_GetMemberValue("Count", 0).f_Integer();
}

// Array operations
if (Json.f_IsArray())
{
	for (auto const &Element : Json.f_Array())
	{
		// Process element
	}
}
```

### Type Conversion
```cpp
// Safe type conversion with defaults
NStr::CStr StringValue = Json.f_AsString("default");
int64 IntValue = Json.f_AsInteger(0);
fp64 FloatValue = Json.f_AsFloat(0.0);
bool BoolValue = Json.f_AsBoolean(false);

// Direct type access (throws on wrong type)
NStr::CStr &String = Json.f_String();
int64 &Integer = Json.f_Integer();
fp64 &Float = Json.f_Float();
bool &Boolean = Json.f_Boolean();
```

## Performance Characteristics

### JSON Variants
- **CJsonOrdered**: Preserves insertion order, best for APIs and user-facing data
- **CJsonSorted**: Auto-sorts keys, best for comparison and hashing, uses less memory and is faster

### Stream Support
The module supports efficient streaming for large JSON documents:
```cpp
// Binary stream serialization
NContainer::CByteVector ByteVector = NStream::fg_ToByteVector(Json);
CJsonOrdered Restored = NStream::fg_FromByteVector<CJsonOrdered>(ByteVector);
```

## Testing

The module includes comprehensive tests in the `Test/` directory:
- `Test_Malterlib_Encoding_Base64.cpp` - Base64 encoding tests
- `Test_Malterlib_Encoding_Bin128.cpp` - Bin128 tests
- `Test_Malterlib_Encoding_Json.cpp` - Core JSON functionality tests
- `Test_Malterlib_Encoding_EJson.cpp` - Enhanced JSON tests
- `Test_Malterlib_Encoding_JsonPerformance.cpp` - Performance benchmarks
- `Test_Malterlib_Encoding_JsonShared.h` - Shared test utilities

Run tests with:
```bash
./mib build Tests macOS x86_64 Debug
/opt/Deploy/Tests/RunAllTests --paths '["Malterlib/Encoding*"]'
```

## Common Use Cases

### 1. Configuration Files
```cpp
CSimpleJsonDatabase Config("app_config.json");
co_await Config.f_Load();
Config.m_Data["Settings"]["Theme"] = "dark";
co_await Config.f_Save();
```

### 2. API Response Handling
```cpp
{
	auto CaptureScope = co_await (g_CaptureExceptions % "Error parsing API response");

	CJsonOrdered Response = CJsonOrdered::fs_FromString(ApiResponseString);
}

if (Response["status"].f_AsString() == "success")
{
	auto const &Data = Response["data"];
	// Process data
}
```

### 3. Data Serialization
```cpp
struct CUserData
{
	NStr::CStr m_Name;
	int32 m_Age;

	CJsonOrdered f_ToJson() const
	{
		return
			{
				"Name"_j= m_Name
				, "Age"_j= m_Age
			}
		;
	}

	void f_FromJson(CJsonOrdered const &_Json)
	{
		m_Name = _Json["Name"].f_AsString();
		m_Age = (int32)_Json["Age"].f_AsInteger();
	}
};
```

### 4. Pretty Printing
```cpp
// Generate formatted JSON with indentation
NStr::CStr PrettyJson = Json.f_ToString();

// Generate colored JSON for terminal output
NStr::CStr ColoredJson = Json.f_ToStringColored(EAnsiEncodingFlag_AllFeatures);
```

## Important Notes

- The module uses custom memory management with Malterlib allocators
- All string operations use `NStr::CStr` instead of `std::string`
- JSON parsing supports various dialects through `EJsonDialectFlag`
- Binary streams support Base64 encoding transparently
- Thread safety is not guaranteed for individual JSON objects - use appropriate locking or `CSimpleJsonDatabase` for concurrent access
- Performance comparison tests against external libraries are available when enabled

## Error Handling

JSON operations may throw exceptions on:
- Parse errors (invalid JSON syntax)
- Type mismatches (accessing wrong type without checking)
- Invalid operations (accessing members on non-objects)

Always validate JSON structure before accessing:
```cpp
try
{
	CJsonOrdered Json = CJsonOrdered::fs_FromString(InputString);
	// Process JSON
}
catch (NException::CException const &_Exception)
{
	// Handle parse error
	DMibLog(Error, "JSON parse error: {}", _Exception);
}
```
