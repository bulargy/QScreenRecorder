//
//  QCGUtils.h
//
//  Created by Jolin He on 14-1-2.
//  Copyright (c) 2014年 Jolin He. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKit.h>

// Represents NULL point (CoreGraphics only has CGRectNull)
extern const CGPoint QCGPointNull;

// Check if point is Null (CoreGraphics only has CGRectIsNull)
extern bool QCGPointIsNull(CGPoint point);

// Represents NULL size (CoreGraphics only has CGRectNull)
extern const CGSize QCGSizeNull;

// Check if size is Null (CoreGraphics only has CGRectIsNull)
extern bool QCGSizeIsNull(CGSize size);

/*!
 Add rounded rect to current context path.
 @param context
 @param rect
 @param strokeWidth Width of stroke (so that we can inset the rect); Since stroke occurs from center of path we need to inset by half the strong amount otherwise the stroke gets clipped.
 @param cornerRadius Corner radius
 */
void QCGContextAddRoundedRect(CGContextRef context, CGRect rect, CGFloat strokeWidth, CGFloat cornerRadius);

/*!
 Draw rounded rect to current context.
 @param context
 @param rect
 @param fillColor If not NULL, will fill in rounded rect with color
 @param strokeColor Color of stroke
 @param strokeWidth Width of stroke
 @param cornerRadius Radius of rounded corners
 */
void QCGContextDrawRoundedRect(CGContextRef context, CGRect rect, CGColorRef fillColor, CGColorRef strokeColor, CGFloat strokeWidth, CGFloat cornerRadius);

/*!
 Draw (fill and/or stroke) path.
 @param context
 @param path
 @param fillColor If not NULL, will fill in rounded rect with color
 @param strokeColor Color of stroke
 @param strokeWidth Width of stroke
 
 */
void QCGContextDrawPath(CGContextRef context, CGPathRef path, CGColorRef fillColor, CGColorRef strokeColor, CGFloat strokeWidth);

/*!
 Create rounded rect path.
 @param rect
 @param strokeWidth Width of stroke
 @param cornerRadius Radius of rounded corners
 */
CGPathRef QCGPathCreateRoundedRect(CGRect rect, CGFloat strokeWidth, CGFloat cornerRadius);

/*!
 Add line from (x, y) to (x2, y2) to context path.
 @param context
 @param x
 @param y
 @param x2
 @param y2
 */
void QCGContextAddLine(CGContextRef context, CGFloat x, CGFloat y, CGFloat x2, CGFloat y2);

/*!
 Draw line from (x, y) to (x2, y2).
 @param context
 @param x
 @param y
 @param x2
 @param y2
 @param strokeColor Line color
 @param strokeWidth Line width (draw from center of width (x+(strokeWidth/2), y+(strokeWidth/2)))
 */
void QCGContextDrawLine(CGContextRef context, CGFloat x, CGFloat y, CGFloat x2, CGFloat y2, CGColorRef strokeColor, CGFloat strokeWidth);

/*!
 Draws image inside rounded rect.
 
 @param context Context
 @param image Image to draw
 @param imageSize Image size
 @param rect Rect to draw
 @param strokeColor Stroke color
 @param strokeWidth Stroke size
 @param cornerRadius Corner radius for rounded rect
 @param contentMode Content Mode
 @param backgroundColor If image is smaller than rect (and not scaling image), this background color is used.
 */
void QCGContextDrawRoundedRectImage(CGContextRef context, CGImageRef image, CGSize imageSize, CGRect rect, CGColorRef strokeColor, CGFloat strokeWidth, CGFloat cornerRadius, UIViewContentMode contentMode, CGColorRef backgroundColor);

/*!
 Draws image inside rounded rect with shadow.
 
 @param context Context
 @param image Image to draw
 @param imageSize Image size
 @param rect Rect to draw
 @param strokeColor Stroke color
 @param strokeWidth Stroke size
 @param cornerRadius Corner radius for rounded rect
 @param contentMode Content Mode
 @param backgroundColor If image is smaller than rect (and not scaling image), this background color is used.
 @param shadowColor Shadow color (or NULL)
 @param shadowBlur Shadow blur amount
 */
void QCGContextDrawRoundedRectImageWithShadow(CGContextRef context, CGImageRef image, CGSize imageSize, CGRect rect, CGColorRef strokeColor, CGFloat strokeWidth, CGFloat cornerRadius, UIViewContentMode contentMode, CGColorRef backgroundColor, CGColorRef shadowColor, CGFloat shadowBlur);

/*!
 Draws image.
 @param context Context
 @param image Image to draw
 @param imageSize Image size
 @param rect Rect to draw
 @param strokeColor Stroke color
 @param strokeWidth Stroke size
 @param contentMode Content mode
 @param backgroundColor If image is smaller than rect (and not scaling image), this background color is used. 
 */
void QCGContextDrawImage(CGContextRef context, CGImageRef image, CGSize imageSize, CGRect rect, CGColorRef strokeColor, CGFloat strokeWidth, UIViewContentMode contentMode, CGColorRef backgroundColor);

/*!
 Figure out the rectangle to fit 'size' into 'inSize'.
 @param size
 @param inSize
 @param fill
 */
CGRect QCGRectScaleAspectAndCenter(CGSize size, CGSize inSize, BOOL fill);

/*!
 Point to place region of size1 into size2, so that its centered.
 @param size1
 @param size2
 */
CGPoint QCGPointToCenter(CGSize size1, CGSize size2);

/*!
 Point to place region of size1 into size2, so that its centered in Y position.
 */
CGPoint QCGPointToCenterY(CGSize size, CGSize inSize);

/*!
 Returns if point is zero origin.
 */
BOOL QCGPointIsZero(CGPoint p);

/*!
 Check if equal.
 @param p1
 @param p2
 */
BOOL QCGPointIsEqual(CGPoint p1, CGPoint p2);

/*!
 Check if equal.
 @param size1
 @param size2
 */
BOOL QCGSizeIsEqual(CGSize size1, CGSize size2);

/*!
 Check if size is zero.
 */
BOOL QCGSizeIsZero(CGSize size);

/*!
 Check if equal within some accuracy.
 @param rect1
 @param rect2
 */
BOOL QCGRectIsEqual(CGRect rect1, CGRect rect2);

/*!
 Returns a rect that is centered vertically in inRect but horizontally unchanged
 @param rect The inner rect
 @param inRect The rect to center inside of
 */
CGRect QCGRectToCenterYInRect(CGRect rect, CGRect inRect);

/*!
 @deprecated Behavior of QCGRectToCenterYInRect is more intuitive
 Returns a rect that is centered vertically in a region with the same size as inRect but horizontally unchanged
 @param rect The inner rect
 @param inRect The rect with the size to center inside of
 */
CGRect QCGRectToCenterY(CGRect rect, CGRect inRect);

/*!
 TODO(gabe): Document
 */
CGPoint QCGPointToRight(CGSize size, CGSize inSize);

/*!
 Center size in size.
 @param size Size for element to center
 @param inSize Containing size
 @result Centered on x and y, returning a size same as size (1st argument)
 */
CGRect QCGRectToCenter(CGSize size, CGSize inSize);

BOOL QCGSizeIsEmpty(CGSize size);

/*!
 TODO(gabe): Document
 */
CGRect QCGRectToCenterInRect(CGSize size, CGRect inRect);

/*!
 TODO(gabe): Document
 */
CGFloat QCGFloatToCenter(CGFloat length, CGFloat inLength, CGFloat min);

/*!
 Adds two rectangles.
 TODO(gabe): Document
 */
CGRect QCGRectAdd(CGRect rect1, CGRect rect2);


/*!
 Get rect to right align width inside inWidth with maxWidth and padding on the right.
 */
CGRect QCGRectRightAlign(CGFloat y, CGFloat width, CGFloat inWidth, CGFloat maxWidth, CGFloat padRight, CGFloat height);

/*!
 Right-align rect with inRect.
 If rect's width is larger than withRect, rect.origin.x will be smaller than withRect.origin.x.
 */
CGRect QCGRectRightAlignWithRect(CGRect rect, CGRect withRect);

/*!
 Copy of CGRect with (x, y) origin set to 0.
 */
CGRect QCGRectZeroOrigin(CGRect rect);

/*!
 Set size on rect.
 */
CGRect QCGRectSetSize(CGRect rect, CGSize size);

/*!
 Set height on rect.
 */
CGRect QCGRectSetHeight(CGRect rect, CGFloat height);

/*
 Set width on rect.
 */
CGRect QCGRectSetWidth(CGRect rect, CGFloat width);

/*!
 Set x on rect.
 */
CGRect QCGRectSetX(CGRect rect, CGFloat x);

/*!
 Set y on rect.
 */
CGRect QCGRectSetY(CGRect rect, CGFloat y);


CGRect QCGRectSetOrigin(CGRect rect, CGFloat x, CGFloat y);

CGRect QCGRectSetOriginPoint(CGRect rect, CGPoint p);

CGRect QCGRectOriginSize(CGPoint origin, CGSize size);

CGRect QCGRectAddPoint(CGRect rect, CGPoint p);

CGRect QCGRectAddHeight(CGRect rect, CGFloat height);

CGRect QCGRectAddX(CGRect rect, CGFloat add);

CGRect QCGRectAddY(CGRect rect, CGFloat add);

/*!
 Bottom right point in rect. (x + width, y + height).
 */
CGPoint QCGPointBottomRight(CGRect rect);

CGFloat QCGDistanceBetween(CGPoint pointA, CGPoint pointB);

/*!
 Returns a rect that is inset inside of size.
 */
CGRect QCGRectWithInsets(CGSize size, UIEdgeInsets insets);

#pragma mark Border Styles

// Border styles:
// So far only borders for the group text field; And allow you to have top, middle, middle, middle, bottom.
//
//   QUIBorderStyleNormal
//   -------
//   |     |
//   -------
//
//   QUIBorderStyleRoundedTop:
//   ╭----╮
//   |     |
//
//
//   QUIBorderStyleTopLeftRight
//   -------  
//   |     |
//
//  
//   QUIBorderStyleRoundedBottom
//   -------
//   |     |
//   ╰----╯
//
typedef enum {
  QUIBorderStyleNone = 0,
  QUIBorderStyleNormal, // Straight top, right, botton, left
  QUIBorderStyleRounded, // Rounded top, right, bottom, left
  QUIBorderStyleTopOnly, // Top (straight) only
  QUIBorderStyleBottomOnly, // Bottom (straight) only
  QUIBorderStyleTopBottom, // Top and bottom only
  QUIBorderStyleRoundedTop, // Rounded top with left and right sides (no bottom)
  QUIBorderStyleTopLeftRight, // Top, left and right sides (no bottom)
  QUIBorderStyleBottomLeftRight, // Bottom, left and right sides (no top)
  QUIBorderStyleRoundedBottom, // Rounded bottom

  QUIBorderStyleRoundedTopOnly, // Rounded top with no sides
  QUIBorderStyleRoundedLeftCap, // Rounded left segment
  QUIBorderStyleRoundedRightCap, // Rounded right segment
  QUIBorderStyleRoundedBack, // Rounded back button
  
  QUIBorderStyleRoundedTopWithBotton, // Rounded top with left and right sides (with bottom)
  QUIBorderStyleRoundedBottomLeftRight, // Rounded bottom (no top)
} QUIBorderStyle;

CGPathRef QCGPathCreateStyledRect(CGRect rect, QUIBorderStyle style, CGFloat strokeWidth, CGFloat cornerRadius);

/*!
 Create path for line.
 @param x1
 @param y1
 @param x2
 @param y2
 */
CGPathRef QCGPathCreateLine(CGFloat x1, CGFloat y1, CGFloat x2, CGFloat y2);

void QCGContextAddStyledRect(CGContextRef context, CGRect rect, QUIBorderStyle style, CGFloat strokeWidth, CGFloat cornerRadius);

void QCGContextDrawBorder(CGContextRef context, CGRect rect, QUIBorderStyle style, CGColorRef fillColor, CGColorRef strokeColor, CGFloat strokeWidth, CGFloat cornerRadius);

void QCGContextDrawBorderWithShadow(CGContextRef context, CGRect rect, QUIBorderStyle style, CGColorRef fillColor, CGColorRef strokeColor, CGFloat strokeWidth, CGFloat cornerRadius, CGColorRef shadowColor, CGFloat shadowBlur, BOOL saveRestore);

void QCGContextDrawRect(CGContextRef context, CGRect rect, CGColorRef fillColor, CGColorRef strokeColor, CGFloat strokeWidth);

#pragma mark Colors

void QCGColorGetComponents(CGColorRef color, CGFloat *red, CGFloat *green, CGFloat *blue, CGFloat *alpha);

#pragma mark Shading

typedef enum {
  QUIShadingTypeUnknown = -1,
  QUIShadingTypeNone = 0,
  QUIShadingTypeLinear, // Linear color blend (for color to color2)
  QUIShadingTypeHorizontalEdge, // Horizontal edge (for color to color2 and color3 to color4)
  QUIShadingTypeHorizontalReverseEdge, // Horizontal edge reversed
  QUIShadingTypeExponential,
  QUIShadingTypeMetalEdge,
} QUIShadingType;

void QCGContextDrawShadingWithHeight(CGContextRef context, CGColorRef color, CGColorRef color2, CGColorRef color3, CGColorRef color4, CGFloat height, QUIShadingType shadingType);

void QCGContextDrawShading(CGContextRef context, CGColorRef color, CGColorRef color2, CGColorRef color3, CGColorRef color4, CGPoint start, CGPoint end, QUIShadingType shadingType, 
                            BOOL extendStart, BOOL extendEnd);


/*!
 Convert rect for size with content mode.
 @param rect Bounds
 @param size Size of view
 @param contentMode Content mode
 */
CGRect QCGRectConvert(CGRect rect, CGSize size, UIViewContentMode contentMode);

/*!
 Description for content mode.
 For debugging.
 */
NSString *QNSStringFromUIViewContentMode(UIViewContentMode contentMode);

/*!
 Scale a CGRect's size while maintaining a fixed center point.
 @param rect CGRect to scale
 @param scale Scale factor by which to increaase the size of the rect
 */
CGRect QCGRectScaleFromCenter(CGRect rect, CGFloat scale);


void QCGTransformHSVRGB(float *components);
void QTransformRGBHSV(float *components);

void QCGContextDrawLinearGradient(CGContextRef context, CGRect rect, CGColorRef startColor, CGColorRef  endColor);

void QCGContextDrawLinearGradientWithColors(CGContextRef context, CGRect rect, NSArray */*of CGColorRef*/colors, CGFloat *locations);

UIImage *QCreateVerticalGradientImage(CGFloat height, CGColorRef topColor, CGColorRef bottomColor);


/*!
 Get a rounded corner mask. For example, for using as a CALayer mask.
 */
UIImage *QCGContextRoundedMask(CGRect rect, CGFloat cornerRadius);
