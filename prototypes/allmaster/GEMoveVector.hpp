#ifndef _GE_MOVEVECTOR_HEADER_
#define	_GE_MOVEVECTOR_HEADER_

class GEMoveVector
{
	public:
		GEMoveVector();
		GEMoveVector(const GEMoveVector& rhs);
		~GEMoveVector();
		
		const GEMoveVector operator +(const int rhs) const;
		const GEMoveVector operator +(const GEMoveVector& rhs) const;
		const GEMoveVector operator *(const int rhs) const;
		const GEMoveVector operator *(const GEMoveVector& rhs) const;
		
		GEMoveVector& operator =(const GEMoveVector& rhs);
		GEMoveVector& operator +=(const int rhs);
		GEMoveVector& operator +=(const GEMoveVector& rhs);
		GEMoveVector& operator *=(const int rhs);
		GEMoveVector& operator *=(const GEMoveVector& rhs);
		
		void	SetFx(int fx);
		void	SetFy(int fy);
		int		GetFx() const;
		int		GetFy() const;
		
//		void	Follow(const GEMoveVector* p_vector);
		
	
	private:
		int		m_nFx;
		int		m_nFy;

		GEMoveVector*	m_pFollow;
};

#endif // _GE_MOVEVECTOR_HEADER_
