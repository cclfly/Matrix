#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <valarray>
#include <string>

template<std::size_t M, std::size_t N, typename Val = double> class Matrix {
public:
    Matrix() : m_data(M*N) {}
    Matrix(const Matrix &othr) : m_data(othr.m_data) {}
    Matrix(Matrix &&othr) : m_data(std::move(othr.m_data)) {}
    Matrix(Val val) : m_data(val,M*N) {}
    Matrix(const std::valarray<Val> &data) : m_data(data) {}
public:
//    static Matrix && fromVector(Matrix<N,M,Val> &&)
    static Matrix && zero() { return Matrix(0); }
public:
    Matrix<M,1,Val> hSlice(std::size_t n) { static_assert(n<N, "Error"); return m_data[std::slice(n*M,M,1)]; }
    Matrix<1,N,Val> vSlice(std::size_t m) { static_assert(m<M, "Error"); return m_data[std::slice(m,N,M)]; }
public:
    ///
    /// \brief T 矩阵转置
    /// \return 转置矩阵
    ///
    friend class Matrix<N,M,Val>;
    Matrix<N,M,Val> T() {
        Matrix<N,M,Val> mat;
        for(int i = 0; i < M; ++i)
        {
            mat.m_data[std::slice(i*N,N,1)] = m_data[std::slice(i,N,M)];
        }
        return mat;
    }
    ///
    /// \brief I 矩阵的逆
    /// （只有方阵有逆）
    /// \return 逆矩阵
    ///
    typename std::conditional<M==N,Matrix<M,N,Val>,void>::type I() {

    }
private:
    std::valarray<Val> m_data;
public:
    std::string toString() {
        std::string str;
        for(int i = 0; i < M; ++i)
        {
            for(int j = 0; j < N; ++j)
            {
                str.append(std::to_string(m_data[i*N+j]));
                str.append(",");
            }
            str.append(";\n");
        }
        return str;
    }
};

template<std::size_t N, typename Val = double> using Vector = Matrix<1,N,Val>;

#endif // MATRIX_HPP
