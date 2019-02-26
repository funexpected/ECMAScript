#!/usr/bin/env python
import json, os
import xml.etree.ElementTree as ET


MODULE_DIR = os.path.abspath( os.path.dirname(__file__) )
DOCS_DIR = os.path.abspath(os.path.join(MODULE_DIR, "../../doc/classes"))
OUTPUT_FILE = os.path.join(MODULE_DIR, "buitin_api.gen.json");

BUILTIN_CLASSES = [
	'Vector2',
	'Rect2',
	# 'Color',
	# 'Vector3',
]

TYPE_MAP = {
	'int': 'number',
	'float': 'number',
	'bool': 'boolean',
	'String': 'string',
}

METHOD_OP_EQUALS = {
	"arguments": [
		{
			"default_value": None,
			"has_default_value": False,
			"type": "${class_name}"
		}
	],
	"name": "equals",
	"native_method": "operator==",
	"return": "boolean"
}

METHOD_OP_ADD = {
	"arguments": [
		{
			"default_value": None,
			"has_default_value": False,
			"type": "${class_name}"
		}
	],
	"name": "add",
	"native_method": "operator+",
	"return": "${class_name}"
}

METHOD_OP_ADD_ASSIGN = {
	"arguments": [
		{
			"default_value": None,
			"has_default_value": False,
			"type": "${class_name}"
		}
	],
	"name": "add_assign",
	"native_method": "operator+=",
	"return": "this"
}

METHOD_OP_SUB = {
	"arguments": [
		{
			"default_value": None,
			"has_default_value": False,
			"type": "${class_name}"
		}
	],
	"name": "subtract",
	"native_method": "operator-",
	"return": "${class_name}"
}

METHOD_OP_SUB_ASSIGN = {
	"arguments": [
		{
			"default_value": None,
			"has_default_value": False,
			"type": "${class_name}"
		}
	],
	"name": "subtract_assign",
	"native_method": "operator-=",
	"return": "this"
}

METHOD_OP_NEG = {
	"arguments": [],
	"name": "negate",
	"native_method": "operator-",
	"return": "${class_name}"
}

METHOD_OP_LESS = {
	"arguments": [
		{
			"default_value": None,
			"has_default_value": False,
			"type": "${class_name}"
		}
	],
	"name": "less",
	"native_method": "operator<",
	"return": "boolean"
}


METHOD_OP_LESS_OR_EQAUL = {
	"arguments": [
		{
			"default_value": None,
			"has_default_value": False,
			"type": "${class_name}"
		}
	],
	"name": "less_or_equal",
	"native_method": "operator<=",
	"return": "boolean"
}

IGNORED_PROPS = {
	"Rect2": ['end']
}

EXTRAL_METHODS = {
	"Vector2": [
		METHOD_OP_NEG,
		METHOD_OP_EQUALS,
		METHOD_OP_LESS,
		METHOD_OP_LESS_OR_EQAUL,
		METHOD_OP_ADD,
		METHOD_OP_ADD_ASSIGN,
		METHOD_OP_SUB,
		METHOD_OP_SUB_ASSIGN,
	],
	"Rect2": [METHOD_OP_EQUALS],
	"Color": [
		METHOD_OP_NEG,
		METHOD_OP_EQUALS,
		METHOD_OP_LESS,
		METHOD_OP_ADD,
		METHOD_OP_ADD_ASSIGN,
		METHOD_OP_SUB,
		METHOD_OP_SUB_ASSIGN,
	],
}

def apply_parttern(template, values):
	for key in values:
		template = template.replace( '${' + key + '}', values[key])
	return template

def parse_class(cls):
	class_name = cls.get('name')
	ret = {'name': class_name}
	members = []
	methods = []
	constants = []
	ret['properties'] = members
	ret['methods'] = methods
	ret['constants'] = constants
	
	for m in (cls.find("members") if cls.find("members") is not None else []):
		m_dict = dict(m.attrib)
		type = m_dict['type']
		name = m_dict['name']
		if (class_name in IGNORED_PROPS) and (name in IGNORED_PROPS[class_name]):
			continue
		if type in TYPE_MAP:
			type = TYPE_MAP[type]
		members.append({'name': name, 'type': type })
	
	for m in (cls.find("methods") if cls.find("methods") is not None else []):
		m_dict = dict(m.attrib)
		if m_dict['name'] == class_name:
			continue# ignore constructors
		return_type = m.find("return").attrib["type"]
		if return_type in TYPE_MAP:
			return_type = TYPE_MAP[return_type]
		arguments = []
		for arg in m.iter('argument'):
			dictArg = dict(arg.attrib)
			if "dictArg" in dictArg: dictArg.pop("index")
			dictArg["default_value"] = dictArg["default"] if "default" in dictArg else None
			if "default" in dictArg: dictArg.pop("default")
			type = dictArg['type']
			if type in TYPE_MAP:
				type = TYPE_MAP[type]
			arguments.append({
				'type': type,
				'default_value': dictArg['default_value'],
				'has_default_value': "default" in dictArg
			})
		methods.append({
			'name': m_dict['name'],
			'native_method': m_dict['name'],
			'return': return_type,
			'arguments': arguments,
		})
	# add extral methods
	if class_name in EXTRAL_METHODS:
		for em in EXTRAL_METHODS[class_name]:
			methods.append(em)
	for c in (cls.find("constants") if cls.find("constants") is not None else []):
		constants.append(dict(c.attrib))
	return json.loads(apply_parttern(json.dumps(ret), {
		'class_name': class_name,
	}))

def generate_api_json():
	classes = []
	for cls in BUILTIN_CLASSES:
		tree = ET.parse(open(os.path.join(DOCS_DIR, cls + '.xml'), 'r'))
		data = tree.getroot()
		classes.append(parse_class(data))
	json.dump(classes, open(OUTPUT_FILE, 'w', encoding='utf8'), ensure_ascii=False, indent=2, sort_keys=True)
	
if __name__ == "__main__":
	generate_api_json()