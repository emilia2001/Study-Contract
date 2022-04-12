#pragma once
#include <iostream>
#include <string>
using namespace std;

class RepoError
{
	string error;
public:
	RepoError(string msj) : error(msj)
	{

	}

	string get_error()
	{
		return error;
	}
};


class ContractError
{
	string error;
public:
	ContractError(string msj) : error(msj)
	{

	}

	string get_error()
	{
		return error;
	}
};


class ValidatorError
{
	string error;
public:
	ValidatorError(string msj) : error(msj)
	{

	}

	string get_error()
	{
		return error;
	}
};