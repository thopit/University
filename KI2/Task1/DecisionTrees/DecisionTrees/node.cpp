#include "node.h"

#include <iostream>
#include <string>
#include <cmath>

using namespace std;


void node::query()
{
	if (decide())
	{
		cout << "Checking left Node\n";
		left_node_->query();
	}
	else
	{
		cout << "Checking right Node\n";
		right_node_->query();
	}
}

check_bool_node::check_bool_node(bool check_value) : check_value_(check_value)
{
}

bool check_bool_node::decide()
{
	return check_value_ == true;
}


check_number_node::check_number_node(int number, int min, int max) : number_(number), min_(min), max_(max)
{
}

bool check_number_node::decide()
{
	return number_ > min_ && number_ < max_;
}


check_in_vector_node::check_in_vector_node(int value, vector<int> vector) : value_(value), vector_(vector)
{
}

bool check_in_vector_node::decide()
{
	return find(vector_.begin(), vector_.end(), value_) != vector_.end();
}


check_length_node::check_length_node(vec2f vector, float length) : vector_(vector), length_(length)
{
}

bool check_length_node::decide()
{
	return sqrtf(vector_.x * vector_.x + vector_.y * vector_.y) < length_;
}


leaf::leaf(string output) : output_(output)
{
}

void leaf::query()
{
	cout << output_;
}

bool leaf::decide()
{
	return false;
}

void main()
{
	shared_ptr<node> root(new check_bool_node(true));

	shared_ptr<node> child1(new check_bool_node(false));
	shared_ptr<node> child2(new check_bool_node(true));

	shared_ptr<node> leaf1(new leaf("First"));
	shared_ptr<node> leaf2(new leaf("Second"));

	shared_ptr<node> leaf3(new leaf("Third"));
	shared_ptr<node> leaf4(new leaf("Fourth"));

	root->left_node_ = child1;
	root->right_node_ = child2;

	child1->left_node_ = leaf1;
	child1->right_node_ = leaf2;

	child2->left_node_ = leaf3;
	child2->right_node_ = leaf4;

	root->query();
}