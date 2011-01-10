#include "GEMoveVector.hpp"

GEMoveVector::GEMoveVector():m_nFx(0), m_nFy(0) //, m_pFollow(NULL)
{
}

GEMoveVector::GEMoveVector(const GEMoveVector& rhs)
{
	m_nFx = rhs.m_nFx;
	m_nFy = rhs.m_nFy;
}

GEMoveVector::~GEMoveVector()
{
}

GEMoveVector& GEMoveVector::operator =(const GEMoveVector& rhs)
{
	if( &rhs != this ) // not self!
	{
		m_nFx = rhs.m_nFx;
		m_nFy = rhs.m_nFy;
	}
	return *this;
}

GEMoveVector& GEMoveVector::operator +=(const int rhs)
{
	m_nFx += rhs;
	m_nFy += rhs;
	return *this;
}

GEMoveVector& GEMoveVector::operator +=(const GEMoveVector& rhs)
{
	m_nFx += rhs.m_nFx;
	m_nFy += rhs.m_nFy;
	return *this;	
}

GEMoveVector& GEMoveVector::operator *=(const int rhs)
{
	m_nFx *= rhs;
	m_nFy *= rhs;
	return *this;	
}

GEMoveVector& GEMoveVector::operator *=(const GEMoveVector& rhs)
{
	m_nFx *= rhs.m_nFx;
	m_nFy *= rhs.m_nFy;
	return *this;	
}

const GEMoveVector GEMoveVector::operator +(const int rhs) const
{
	GEMoveVector result(*this); // creates a copy of this
	result += rhs; // alter the copy
	return result; // returns the copy!
}

const GEMoveVector GEMoveVector::operator +(const GEMoveVector& rhs) const
{
	return GEMoveVector(*this) += rhs; // condensed form
}

const GEMoveVector GEMoveVector::operator *(const int rhs) const
{
	return GEMoveVector(*this) *= rhs;
}

const GEMoveVector GEMoveVector::operator *(const GEMoveVector& rhs) const
{
	return GEMoveVector(*this) *= rhs;
}

void GEMoveVector::SetFx(int fx)
{
	m_nFx = fx;
}

void GEMoveVector::SetFy(int fy)
{
	m_nFy = fy;
}

int GEMoveVector::GetFx() const
{
//	return (m_pFollow != NULL) ? m_nFx + m_pFollow->GetFx() : m_nFx;
	return m_nFx;
}

int GEMoveVector::GetFy() const
{
//	return (m_pFollow != NULL) ? m_nFy + m_pFollow->GetFy() : m_nFx;
	return m_nFy;
}

/*
void GEMoveVector::Follow(GEMoveVector* p_vector)
{
	m_pFollow = p_vector;
}
*/
