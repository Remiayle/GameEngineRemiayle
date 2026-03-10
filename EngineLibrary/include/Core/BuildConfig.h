/*!
 * @file BuildConfig.h
 * @brief ビルド構成定義
 */

#pragma once

/*!
 * @brief デバッグビルド判定
 *
 * Visual Studio環境を想定し、
 * _DEBUG または DEBUG が定義されている場合をデバッグとする。
 */
#if defined(_DEBUG) || defined(DEBUG)
#define REMIAYLE_DEBUG 1
#else
#define REMIAYLE_DEBUG 0
#endif
