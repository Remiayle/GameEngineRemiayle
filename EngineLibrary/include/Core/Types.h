/*!
 * @file Types.h
 * @brief 基本型エイリアス定義
 */

#pragma once

#include <cstdint>
#include <cstddef>

namespace Remiayle::Core
{
    /*!
     * @brief 符号なし整数型
     */
    using u8 = std::uint8_t;    /**< 8bit符号なし整数 */
    using u16 = std::uint16_t;  /**< 16bit符号なし整数 */
    using u32 = std::uint32_t;  /**< 32bit符号なし整数 */
    using u64 = std::uint64_t;  /**< 64bit符号なし整数 */

    /*!
     * @brief 符号付き整数型
     */
    using i8 = std::int8_t;     /**< 8bit符号付き整数 */
    using i16 = std::int16_t;   /**< 16bit符号付き整数 */
    using i32 = std::int32_t;   /**< 32bit符号付き整数 */
    using i64 = std::int64_t;   /**< 64bit符号付き整数 */

    /*!
     * @brief 浮動小数点型
     */
    using f32 = float;          /**< 32bit浮動小数点数 */
    using f64 = double;         /**< 64bit浮動小数点数 */

    /*!
     * @brief サイズ型
     */
    using usize = std::size_t;  /**< メモリサイズ・配列長などに使用 */
}
