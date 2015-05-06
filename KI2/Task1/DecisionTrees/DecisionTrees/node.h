#pragma once
#include <memory>
#include <vector>

class node
{
public:
	virtual void query();
	virtual bool decide() = 0;

	std::shared_ptr<node> left_node_;
	std::shared_ptr<node> right_node_;
};

class check_bool_node: public node
{
public:
	check_bool_node(bool check_value);

	bool decide();
protected:
	bool check_value_;
};

class check_number_node : public node
{
public:
	check_number_node(int number, int min, int max);

	bool decide();
protected:
	int number_;
	int min_;
	int max_;
};

class check_in_vector_node : public node
{
public:
	check_in_vector_node(int value, std::vector<int> vector);

	bool decide();
protected:
	int value_;
	std::vector<int> vector_;
};

class check_length_node : public node
{
struct vec2f { float x; float y; };

public:
	check_length_node(vec2f vector, float length);

	bool decide();
protected:
	vec2f vector_;
	float length_;
};

class leaf : public node
{
public:
	leaf(std::string output);

	void query();
	bool decide();

protected:
	std::string output_;
};