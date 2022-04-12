#pragma once
#define VectorDinamic_h_
#include "Domain.h"

template <typename TElem>
class IteratorVectorT;

template <typename TElem>
class VectorDinamic
{
private:
	int cp;
	int n;
	TElem* elems;

public:

	friend class IteratorVectorT<TElem>;
	IteratorVectorT<TElem> begin();
	IteratorVectorT<TElem> end();

	VectorDinamic<TElem>() noexcept : cp{ 1 }, n{ 0 }, elems{ new TElem[cp] } {
	}

	//constructor de copiere
	VectorDinamic<TElem>(const VectorDinamic& vd);

	//constructor de asignare
	VectorDinamic<TElem>& operator=(const VectorDinamic& ot);

	void push_back(const TElem& disci);

	int find(const TElem& disci);

	void delete_vd(int poz);

	TElem& get(int poz) const noexcept;

	int size() const noexcept {
		return n;
	}

	//destructor
	~VectorDinamic() {
		delete[] elems;
	}
};

template <typename TElem>
VectorDinamic <TElem>::VectorDinamic(const VectorDinamic& vd)
{
	this->cp = vd.cp;
	this->n = vd.n;
	this->elems = new TElem[cp];
	for (int i = 0; i < vd.n; i++)
	{
		this->elems[i] = vd.elems[i];
	}
}

template <typename TElem>
VectorDinamic<TElem>& VectorDinamic <TElem>::operator=(const VectorDinamic& ot) {
	if (this == &ot)
		return *this;
	delete[] this->elems;
	this->elems = new TElem[ot.cp];
	for (int i = 0; i < ot.n; i++)
	{
		this->elems[i] = ot.elems[i];
	}
	this->cp = ot.cp;
	this->n = ot.n;
	return *this;
}

template <typename TElem>
void VectorDinamic <TElem>::push_back(const TElem& disci)
{
	if (cp == n)
	{
		TElem* aux = new TElem[cp * 2];
		for (int i = 0; i < n; i++)
		{
			aux[i] = elems[i];
		}
		delete[] elems;
		elems = aux;
		cp = cp * 2;
	}
	elems[n++] = disci;
}

template <typename TElem>
int VectorDinamic <TElem>::find(const TElem& disci)
{
	for (int i = 0; i < n; i++)
	{
		if (elems[i] == disci)
			return i;
	}   return -1;
}

template <typename TElem>
void VectorDinamic <TElem>::delete_vd(int poz) {
	for (int i = poz; i < n - 1; i++)
	{
		elems[i] = elems[i + 1];
	}
	n--;
	if (n <= cp / 2)
	{
		TElem* aux = new TElem[cp / 2];
		for (int i = 0; i < n; i++)
		{
			aux[i] = elems[i];
		}
		delete[] elems;
		elems = aux;
		cp = cp / 2;
	}
}

template <typename TElem>
TElem& VectorDinamic <TElem>::get(int poz) const noexcept {
	return elems[poz];
}

template <typename TElem>
IteratorVectorT<TElem> VectorDinamic <TElem>::begin()
{
	return IteratorVectorT<TElem>(*this);
}

template <typename TElem>
IteratorVectorT<TElem> VectorDinamic <TElem>::end()
{
	return IteratorVectorT<TElem>(*this, n);
}







template <typename TElem>
class IteratorVectorT
{
private:
	const VectorDinamic <TElem>& vd;
	int poz = 0;

public:
	IteratorVectorT(const VectorDinamic<TElem>& vd) noexcept : vd{ vd } {}
	IteratorVectorT(const VectorDinamic<TElem>& vd, int poz) noexcept : vd{ vd }, poz{ poz } {}
	TElem& operator*() noexcept;
	IteratorVectorT& operator++() noexcept;
	bool operator==(const IteratorVectorT<TElem>& ot) noexcept;
	bool operator!=(const IteratorVectorT<TElem>& ot) noexcept;
};

template <typename TElem>
TElem& IteratorVectorT<TElem> :: operator*() noexcept {
	return vd.elems[poz];
}

template <typename TElem>
IteratorVectorT<TElem>& IteratorVectorT<TElem> :: operator++() noexcept {
	poz++;
	return *this;
}

template <typename TElem>
bool IteratorVectorT<TElem> :: operator==(const IteratorVectorT<TElem>& ot) noexcept {
	return poz == ot.poz;
}

template <typename TElem>
bool IteratorVectorT<TElem> :: operator!=(const IteratorVectorT<TElem>& ot) noexcept {
	return !(*this == ot);
}