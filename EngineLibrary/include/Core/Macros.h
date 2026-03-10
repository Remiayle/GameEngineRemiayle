/*!
 * @file Macros.h
 * @brief 基本マクロ定義
 */

#pragma once

#include "Core/BuildConfig.h"

/*!
 * @brief コピー禁止マクロ
 */
#define REMIAYLE_NON_COPYABLE(Type) \
    Type(const Type&) = delete;     \
    Type& operator=(const Type&) = delete;

/*!
 * @brief ムーブ禁止マクロ
 */
#define REMIAYLE_NON_MOVABLE(Type) \
    Type(Type&&) = delete;         \
    Type& operator=(Type&&) = delete;

/*!
 * @brief コピーおよびムーブ禁止マクロ
 */
#define REMIAYLE_NON_COPYABLE_MOVABLE(Type) \
    REMIAYLE_NON_COPYABLE(Type)             \
    REMIAYLE_NON_MOVABLE(Type)

/*!
 * @brief 強制インライン指定
 */
#if defined(_MSC_VER)
#define REMIAYLE_FORCE_INLINE __forceinline
#else
#define REMIAYLE_FORCE_INLINE inline
#endif

/*!
 * @brief 未使用引数警告抑制
 * @param x 未使用の引数
 */
#define REMIAYLE_UNUSED(x) (void)(x)

/*!
 * @brief デバッグブレーク
 */
#if REMIAYLE_DEBUG
#if defined(_MSC_VER)
#define REMIAYLE_DEBUG_BREAK() __debugbreak()
#else
#include <csignal>
#define REMIAYLE_DEBUG_BREAK() std::raise(SIGTRAP)
#endif
#else
#define REMIAYLE_DEBUG_BREAK() ((void)0)
#endif
