
//----- (00447C20) --------------------------------------------------------
void __thiscall advManager::CompleteDraw(advManager *ecx0, int left, int top, int a6, int a5)
{
  int v5; // edx@1
  signed int a4; // [sp+10h] [bp-8h]@5
  signed int a4a; // [sp+10h] [bp-8h]@11
  signed int a4b; // [sp+10h] [bp-8h]@20
  signed int a4c; // [sp+10h] [bp-8h]@46
  signed int a4d; // [sp+10h] [bp-8h]@52
  int a3; // [sp+14h] [bp-4h]@7
  int a3a; // [sp+14h] [bp-4h]@13
  int a3b; // [sp+14h] [bp-4h]@17
  int a3c; // [sp+14h] [bp-4h]@23
  int a3d; // [sp+14h] [bp-4h]@26
  int a3e; // [sp+14h] [bp-4h]@30
  int a3f; // [sp+14h] [bp-4h]@33
  int a3g; // [sp+14h] [bp-4h]@36
  int a3h; // [sp+14h] [bp-4h]@40
  int a3i; // [sp+14h] [bp-4h]@43
  int a3j; // [sp+14h] [bp-4h]@48
  int a3k; // [sp+14h] [bp-4h]@54

  PollSound();
  if ( a6 || bShowIt )
  {
    giLimitUpdMinX = -1;
    ecx0->field_1DE = ecx0->viewX;
    ecx0->field_1E2 = ecx0->viewY;
    if ( gbAllBlack )
    {
      ecx0->viewY = 0;
      ecx0->viewX = ecx0->viewY;
    }
    gpMouseManager->couldBeShowMouse = 0;
    ecx0->field_2A2 = 0;
    ecx0->field_2AE = 0;
    for ( a4 = 0; a4 < 15; ++a4 )
    {
      for ( a3 = 0; a3 < 15; ++a3 )
        advManager::DrawCell(ecx0, a3 + left, top + a4, a3, a4, 1, a6); //0ub0000 0001
    }
    for ( a4a = 0; a4a < 15; ++a4a )
    {
      for ( a3a = 0; a3a < 15; ++a3a )
        advManager::DrawCell(ecx0, a3a + left, top + a4a, a3a, a4a, 255, a6); //0ub1000 0000
    }
	
    for ( a3b = 0; a3b < 15; ++a3b )  //interface outline
      advManager::DrawCell(ecx0, a3b + left, top, a3b, 0, 2, a6);  //0ub0000 0010
    
	for ( a4b = 1; a4b < 15; ++a4b ) 
    {
      PollSound();
      if ( ecx0->field_27E <= 4 )  //field_27e==S1cursorDirection  //scrolling-related?  and/or the interface
      {
        for ( a3e = 14; a3e >= 0; --a3e )
          advManager::DrawCell(ecx0, a3e + left, top + a4b - 1, a3e, a4b - 1, 8, a6); //0ub0000 1000
        for ( a3f = 14; a3f >= 0; --a3f )
          advManager::DrawCell(ecx0, a3f + left, top + a4b - 1, a3f, a4b - 1, 4, a6); //0ub0000 0100
      }
      else
      {
        for ( a3c = 0; a3c < 15; ++a3c )
          advManager::DrawCell(ecx0, a3c + left, top + a4b - 1, a3c, a4b - 1, 8, a6); //0ub0000 1000
        for ( a3d = 0; a3d < 15; ++a3d )
          advManager::DrawCell(ecx0, a3d + left, top + a4b - 1, a3d, a4b - 1, 4, a6); //0ub0000 0100
      }
      for ( a3g = 0; a3g < 15; ++a3g )
        advManager::DrawCell(ecx0, a3g + left, top + a4b, a3g, a4b, 2, a6);  //0ub0000 0010
    }
    
	for ( a3h = 0; a3h < 15; ++a3h ) //interface outline
      advManager::DrawCell(ecx0, a3h + left, top + 14, a3h, 14, 8, a6); //0ub0000 1000
    for ( a3i = 0; a3i < 15; ++a3i ) //interface outline
      advManager::DrawCell(ecx0, a3i + left, top + 14, a3i, 14, 4, a6); //0ub0000 0100
    
	for ( a4c = 0; a4c < 15; ++a4c )
    {
      for ( a3j = 0; a3j < 15; ++a3j )
        advManager::DrawCell(ecx0, a3j + left, top + a4c, a3j, a4c, 64, a6); //0ub0100 0000  //0x40
    }
    for ( a4d = 0; a4d < 15; ++a4d )
    {
      for ( a3k = 0; a3k < 15; ++a3k )
        advManager::DrawCell(ecx0, a3k + left, top + a4d, a3k, a4d, 32, a6); //0ub0010 0000  //0x20
    }
    advManager::DrawAdventureBorder((int)ecx0, v5);
    gpMouseManager->couldBeShowMouse = 1;
    PollSound();
    if ( a5 )
      advManager::UpdBottomView(ecx0, 0, 1, 1);
    if ( gbAllBlack )
    {
      ecx0->viewX = ecx0->field_1DE;
      ecx0->viewY = ecx0->field_1E2;
    }
  }
}


//----- (00448500) --------------------------------------------------------
void __thiscall advManager::DrawCell(advManager *this, int x, int y, int a3, int a4, char DRAW_MASK, int a6)
{
  signed int v8; // [sp+10h] [bp-18h]@201
  signed int v9; // [sp+14h] [bp-14h]@194
  int v10; // [sp+1Ch] [bp-Ch]@199
  int v11; // [sp+20h] [bp-8h]@182
  int v12; // [sp+24h] [bp-4h]@127

  if ( !a6 && !bShowIt )
    return;
  dword_524D10 = 32 * a3;
  ::y = 32 * a4;
  currentlyDrawnMapTile = advManager::GetCell(this, x, y);
  if ( !gbAllBlack && ((signed __int64)__PAIR__(y, x) < 0 || x >= MAP_WIDTH || y >= MAP_HEIGHT) ) //outside map bounds
  { //outside map bounds, draw stone
    idx = -1;
    if ( x == -1 )
    {
      if ( y == -1 )
      {
        idx = 16;
      }
      else if ( y == MAP_HEIGHT )
      {
        idx = 19;
      }
      else if ( y >= 0 && y < MAP_HEIGHT )
      {
        idx = (y & 3) + 32;
      }
    }
    else if ( x == MAP_WIDTH )
    {
      if ( y == -1 )
      {
        idx = 17;
      }
      else if ( y == MAP_HEIGHT )
      {
        idx = 18;
      }
      else if ( y >= 0 && y < MAP_HEIGHT )
      {
        idx = (y & 3) + 24;
      }
    }
    else if ( y == -1 )
    {
      if ( x >= 0 && x < MAP_WIDTH )
        idx = (x & 3) + 20;
    }
    else if ( y == MAP_HEIGHT && x >= 0 && x < MAP_WIDTH )
    {
      idx = (x & 3) + 28;
    }
    if ( idx == -1 )
      idx = (((unsigned __int64)(x + 16) >> 32) ^ abs(x + 16) & 3)
          + 4 * ((((unsigned __int64)(y + 16) >> 32) ^ abs(y + 16) & 3) - ((unsigned __int64)(y + 16) >> 32))
          - ((unsigned __int64)(x + 16) >> 32);
    TileToBitmap(this->stonTileset, idx, gpWindowManager->screenBuffer, dword_524D10, ::y);
    return;
  }
  if ( !gbAllBlack && (unsigned __int8)(*(&mapExtra[x] + MAP_WIDTH * y) & giCurWatchPlayerBit) || gbDrawingPuzzle )
  {
    dword_524CF8 = 0;
  }
  else
  {
    dword_524CF8 = 1;
    if ( gbAllBlack )
      dword_524D24 = 0;
    else
      dword_524D24 = advManager::GetCloudLookup(x, y);
    if ( !dword_524D24 )
    {
      if ( DRAW_MASK & 0x20 )
        TileToBitmap(this->clofTileset, ((_BYTE)x + (_BYTE)y) & 3, gpWindowManager->screenBuffer, dword_524D10, ::y);
      return;
    }
    if ( dword_524D24 < 100 )
    {
      dword_524CD4 = 0;
    }
    else
    {
      dword_524CD4 = 1;
      dword_524D24 -= 100;
    }
    if ( (dword_524D24 == 1 || dword_524D24 == 5) && x & 1 )
      ++dword_524D24;
    if ( dword_524D24 == 3 && y & 1 )
      ++dword_524D24;
  }
  if ( !(DRAW_MASK & 0x20) || gbDrawingPuzzle ) //0x20 == 32 == 0ub0010 0000
  {
    if ( DRAW_MASK & 1 )//0ub0000 0001
    {
      LOWORD(word_524CAC) = currentlyDrawnMapTile->displayFlags;
      LOWORD(word_524CAC) = (_WORD)word_524CAC << 14;
      LOWORD(word_524CAC) = word_524CAC | currentlyDrawnMapTile->groundIndex;
      TileToBitmap(this->groundTileset, (unsigned __int16)word_524CAC, gpWindowManager->screenBuffer, dword_524D10, ::y);
      if ( currentlyDrawnMapTile->field_4_1_1_isShadow_1_13_extraInfo & 1 //layer == 1 (lakes)
        && (!gbDrawingPuzzle
         || (((unsigned __int8)currentlyDrawnMapTile->bitfield_1_hasObject_1_isRoad_6_objTileset >> 2) & 0x3F) != 56 //TILESET_OBJECT_DIRT = 56,
         || currentlyDrawnMapTile->objectIndex != 140) ) //a hole?
      {
        if ( !gbDrawingPuzzle
          || bPuzzleDraw[((unsigned __int8)currentlyDrawnMapTile->bitfield_1_hasObject_1_isRoad_6_objTileset >> 2) & 0x3F] )
        {
          IconToBitmap(
            (icon *)this->field_CE[((unsigned __int8)currentlyDrawnMapTile->bitfield_1_hasObject_1_isRoad_6_objTileset >> 2) & 0x3F],
            gpWindowManager->screenBuffer,
            dword_524D10,
            ::y,
            currentlyDrawnMapTile->objectIndex,
            0,
            0,
            0,
            0x1E0u,
            480,
            0);
          if ( currentlyDrawnMapTile->bitfield_1_hasObject_1_isRoad_6_objTileset & 1 ) //if object is animated
          {
            number_of_animation_frames = GetIconEntry(
                             (icon *)this->field_CE[((unsigned __int8)currentlyDrawnMapTile->bitfield_1_hasObject_1_isRoad_6_objTileset >> 2) & 0x3F],
                             currentlyDrawnMapTile->objectIndex)->someSortOfLength & 0x1F;
            IconToBitmap(
              (icon *)this->field_CE[((unsigned __int8)currentlyDrawnMapTile->bitfield_1_hasObject_1_isRoad_6_objTileset >> 2) & 0x3F],
              gpWindowManager->screenBuffer,
              dword_524D10,
              ::y,
              currentlyDrawnMapTile->objectIndex + this->current_animation_fram % number_of_animation_frames + 1,
              0,
              0,
              0,
              0x1E0u,
              480,
              0);
          }
        }
      }
      if ( currentlyDrawnMapTile->extraIdx
        && *(&this->map->cellExtras->objectIndex + 8 * currentlyDrawnMapTile->extraIdx - currentlyDrawnMapTile->extraIdx) != 255 )
        currentlyDrawingMapCellExtra = (mapCellExtra *)((char *)this->map->cellExtras
                                                      + 8 * currentlyDrawnMapTile->extraIdx
                                                      - currentlyDrawnMapTile->extraIdx);
      else
        currentlyDrawingMapCellExtra = 0;
      while ( currentlyDrawingMapCellExtra )
      {
        if ( currentlyDrawingMapCellExtra->field_4 & 1
          && (!gbDrawingPuzzle || bPuzzleDraw[(currentlyDrawingMapCellExtra->_1_q_7_objTileset >> 1) & 0x7F]) )
        {
          IconToBitmap(
            (icon *)this->field_CE[(currentlyDrawingMapCellExtra->_1_q_7_objTileset >> 1) & 0x7F],
            gpWindowManager->screenBuffer,
            dword_524D10,
            ::y,
            currentlyDrawingMapCellExtra->objectIndex,
            0,
            0,
            0,
            0x1E0u,
            480,
            0);
          if ( currentlyDrawingMapCellExtra->_1_q_7_objTileset & 1 )
          {
            number_of_animation_frames = GetIconEntry(
                             (icon *)this->field_CE[(currentlyDrawingMapCellExtra->_1_q_7_objTileset >> 1) & 0x7F],
                             currentlyDrawingMapCellExtra->objectIndex)->someSortOfLength & 0x1F;
            IconToBitmap(
              (icon *)this->field_CE[(currentlyDrawingMapCellExtra->_1_q_7_objTileset >> 1) & 0x7F],
              gpWindowManager->screenBuffer,
              dword_524D10,
              ::y,
              currentlyDrawingMapCellExtra->objectIndex + this->field_202 % number_of_animation_frames + 1,
              0,
              0,
              0,
              0x1E0u,
              480,
              0);
          }
        }
        if ( currentlyDrawingMapCellExtra->nextIdx
          && *(&this->map->cellExtras->objectIndex
             + 8 * currentlyDrawingMapCellExtra->nextIdx
             - currentlyDrawingMapCellExtra->nextIdx) != 255 )
          currentlyDrawingMapCellExtra = (mapCellExtra *)((char *)this->map->cellExtras
                                                        + 8 * currentlyDrawingMapCellExtra->nextIdx
                                                        - currentlyDrawingMapCellExtra->nextIdx);
        else
          currentlyDrawingMapCellExtra = 0;
      }
      if ( (currentlyDrawnMapTile->field_4_1_1_isShadow_1_13_extraInfo >> 1) & 1
        && !(currentlyDrawnMapTile->field_4_1_1_isShadow_1_13_extraInfo & 1)
        && (!gbDrawingPuzzle
         || bPuzzleDraw[((unsigned __int8)currentlyDrawnMapTile->bitfield_1_hasObject_1_isRoad_6_objTileset >> 2) & 0x3F]) )
      {
        IconToBitmap(
          (icon *)this->field_CE[((unsigned __int8)currentlyDrawnMapTile->bitfield_1_hasObject_1_isRoad_6_objTileset >> 2) & 0x3F],
          gpWindowManager->screenBuffer,
          dword_524D10,
          ::y,
          currentlyDrawnMapTile->objectIndex,
          0,
          0,
          0,
          0x1E0u,
          480,
          0);
        if ( currentlyDrawnMapTile->bitfield_1_hasObject_1_isRoad_6_objTileset & 1 )
        {
          number_of_animation_frames = GetIconEntry(
                           (icon *)this->field_CE[((unsigned __int8)currentlyDrawnMapTile->bitfield_1_hasObject_1_isRoad_6_objTileset >> 2) & 0x3F],
                           currentlyDrawnMapTile->objectIndex)->someSortOfLength & 0x1F;
          IconToBitmap(
            (icon *)this->field_CE[((unsigned __int8)currentlyDrawnMapTile->bitfield_1_hasObject_1_isRoad_6_objTileset >> 2) & 0x3F],
            gpWindowManager->screenBuffer,
            dword_524D10,
            ::y,
            currentlyDrawnMapTile->objectIndex + this->field_202 % number_of_animation_frames + 1,
            0,
            0,
            0,
            0x1E0u,
            480,
            0);
        }
      }
      if ( currentlyDrawnMapTile->extraIdx
        && *(&this->map->cellExtras->objectIndex + 8 * currentlyDrawnMapTile->extraIdx - currentlyDrawnMapTile->extraIdx) != 255 )
        currentlyDrawingMapCellExtra = (mapCellExtra *)((char *)this->map->cellExtras
                                                      + 8 * currentlyDrawnMapTile->extraIdx
                                                      - currentlyDrawnMapTile->extraIdx);
      else
        currentlyDrawingMapCellExtra = 0;
      while ( currentlyDrawingMapCellExtra )
      {
        if ( ((unsigned __int8)currentlyDrawingMapCellExtra->field_4 >> 1) & 1
          && !(currentlyDrawingMapCellExtra->field_4 & 1)
          && (!gbDrawingPuzzle || bPuzzleDraw[(currentlyDrawingMapCellExtra->_1_q_7_objTileset >> 1) & 0x7F]) )
        {
          IconToBitmap(
            (icon *)this->field_CE[(currentlyDrawingMapCellExtra->_1_q_7_objTileset >> 1) & 0x7F],
            gpWindowManager->screenBuffer,
            dword_524D10,
            ::y,
            currentlyDrawingMapCellExtra->objectIndex,
            0,
            0,
            0,
            0x1E0u,
            480,
            0);
          if ( currentlyDrawingMapCellExtra->_1_q_7_objTileset & 1 )
          {
            number_of_animation_frames = GetIconEntry(
                             (icon *)this->field_CE[(currentlyDrawingMapCellExtra->_1_q_7_objTileset >> 1) & 0x7F],
                             currentlyDrawingMapCellExtra->objectIndex)->someSortOfLength & 0x1F;
            IconToBitmap(
              (icon *)this->field_CE[(currentlyDrawingMapCellExtra->_1_q_7_objTileset >> 1) & 0x7F],
              gpWindowManager->screenBuffer,
              dword_524D10,
              ::y,
              currentlyDrawingMapCellExtra->objectIndex + this->field_202 % number_of_animation_frames + 1,
              0,
              0,
              0,
              0x1E0u,
              480,
              0);
          }
        }
        if ( currentlyDrawingMapCellExtra->nextIdx
          && *(&this->map->cellExtras->objectIndex
             + 8 * currentlyDrawingMapCellExtra->nextIdx
             - currentlyDrawingMapCellExtra->nextIdx) != 255 )
          currentlyDrawingMapCellExtra = (mapCellExtra *)((char *)this->map->cellExtras
                                                        + 8 * currentlyDrawingMapCellExtra->nextIdx
                                                        - currentlyDrawingMapCellExtra->nextIdx);
        else
          currentlyDrawingMapCellExtra = 0;
      }
    }
    if ( DRAW_MASK & 2 ) //0ub0000 0010
    {
      if ( currentlyDrawnMapTile->objectIndex != 255
        && !(currentlyDrawnMapTile->field_4_1_1_isShadow_1_13_extraInfo & 1)  //layer == 1 (some lakes)
        && !((currentlyDrawnMapTile->field_4_1_1_isShadow_1_13_extraInfo >> 1) & 1)
        && !((currentlyDrawnMapTile->field_4_1_1_isShadow_1_13_extraInfo >> 2) & 1)
        && (((unsigned __int8)currentlyDrawnMapTile->bitfield_1_hasObject_1_isRoad_6_objTileset >> 2) & 0x3F) != 12
        && (!gbDrawingPuzzle
         || bPuzzleDraw[((unsigned __int8)currentlyDrawnMapTile->bitfield_1_hasObject_1_isRoad_6_objTileset >> 2) & 0x3F]) )
      {
        IconToBitmap(
          (icon *)this->field_CE[((unsigned __int8)currentlyDrawnMapTile->bitfield_1_hasObject_1_isRoad_6_objTileset >> 2) & 0x3F],
          gpWindowManager->screenBuffer,
          dword_524D10,
          ::y,
          currentlyDrawnMapTile->objectIndex,
          0,
          0,
          0,
          0x1E0u,
          480,
          0);
        if ( currentlyDrawnMapTile->bitfield_1_hasObject_1_isRoad_6_objTileset & 1 )
        {
          number_of_animation_frames = GetIconEntry(
                           (icon *)this->field_CE[((unsigned __int8)currentlyDrawnMapTile->bitfield_1_hasObject_1_isRoad_6_objTileset >> 2) & 0x3F],
                           currentlyDrawnMapTile->objectIndex)->someSortOfLength & 0x1F;
          v12 = this->field_202 % number_of_animation_frames;
          if ( currentlyDrawnMapTile->objType == 223 )
          {
            if ( (unsigned __int8)(currentlyDrawnMapTile->field_4_1_1_isShadow_1_13_extraInfo >> 8) >> -5 )
              v12 = this->field_202 % (number_of_animation_frames - 1);
            else
              v12 = number_of_animation_frames - 1;
          }
          IconToBitmap(
            (icon *)this->field_CE[((unsigned __int8)currentlyDrawnMapTile->bitfield_1_hasObject_1_isRoad_6_objTileset >> 2) & 0x3F],
            gpWindowManager->screenBuffer,
            dword_524D10,
            ::y,
            v12 + currentlyDrawnMapTile->objectIndex + 1,
            0,
            0,
            0,
            0x1E0u,
            480,
            0);
        }
      }
      if ( currentlyDrawnMapTile->extraIdx
        && *(&this->map->cellExtras->objectIndex + 8 * currentlyDrawnMapTile->extraIdx - currentlyDrawnMapTile->extraIdx) != 255 )
        currentlyDrawingMapCellExtra = (mapCellExtra *)((char *)this->map->cellExtras
                                                      + 8 * currentlyDrawnMapTile->extraIdx
                                                      - currentlyDrawnMapTile->extraIdx);
      else
        currentlyDrawingMapCellExtra = 0;
      while ( currentlyDrawingMapCellExtra )
      {
        if ( !(currentlyDrawingMapCellExtra->field_4 & 1)
          && !(((unsigned __int8)currentlyDrawingMapCellExtra->field_4 >> 1) & 1)
          && !(((unsigned __int8)currentlyDrawingMapCellExtra->field_4 >> 2) & 1)
          && ((currentlyDrawingMapCellExtra->_1_q_7_objTileset >> 1) & 0x7F) != 12
          && (!gbDrawingPuzzle || bPuzzleDraw[(currentlyDrawingMapCellExtra->_1_q_7_objTileset >> 1) & 0x7F]) )
        {
          IconToBitmap(
            (icon *)this->field_CE[(currentlyDrawingMapCellExtra->_1_q_7_objTileset >> 1) & 0x7F],
            gpWindowManager->screenBuffer,
            dword_524D10,
            ::y,
            currentlyDrawingMapCellExtra->objectIndex,
            0,
            0,
            0,
            0x1E0u,
            480,
            0);
          if ( currentlyDrawingMapCellExtra->_1_q_7_objTileset & 1 )
          {
            number_of_animation_frames = GetIconEntry(
                             (icon *)this->field_CE[(currentlyDrawingMapCellExtra->_1_q_7_objTileset >> 1) & 0x7F],
                             currentlyDrawingMapCellExtra->objectIndex)->someSortOfLength & 0x1F;
            IconToBitmap(
              (icon *)this->field_CE[(currentlyDrawingMapCellExtra->_1_q_7_objTileset >> 1) & 0x7F],
              gpWindowManager->screenBuffer,
              dword_524D10,
              ::y,
              currentlyDrawingMapCellExtra->objectIndex + this->field_202 % number_of_animation_frames + 1,
              0,
              0,
              0,
              0x1E0u,
              480,
              0);
          }
        }
        if ( currentlyDrawingMapCellExtra->nextIdx
          && *(&this->map->cellExtras->objectIndex
             + 8 * currentlyDrawingMapCellExtra->nextIdx
             - currentlyDrawingMapCellExtra->nextIdx) != 255 )
          currentlyDrawingMapCellExtra = (mapCellExtra *)((char *)this->map->cellExtras
                                                        + 8 * currentlyDrawingMapCellExtra->nextIdx
                                                        - currentlyDrawingMapCellExtra->nextIdx);
        else
          currentlyDrawingMapCellExtra = 0;
      }
    }
    if ( (DRAW_MASK & 8 || DRAW_MASK & 0x80) && !gbDrawingPuzzle ) //0ub0000 1000
    {
      dword_524D04 = 0;
      dword_524CDC = 0;
      if ( DRAW_MASK & 8 ) //0ub0000 1000
      {
        if ( x > 0 )
        {
          dword_524D08 = (int)advManager::GetCell(this, x - 1, y);
          if ( *(_BYTE *)(dword_524D08 + 9) == 151 ) //haunted mines
          {
            dword_524EA8 = (int)&gpGame->mines[(unsigned __int8)((unsigned __int8)(*(_WORD *)(dword_524D08 + 4) >> 8) >> -5)];
            if ( *(_BYTE *)(dword_524EA8 + 3) == 59 )
            {
              IconToBitmap(
                (icon *)this->field_CE[10], 
                gpWindowManager->screenBuffer,
                dword_524D10 - 16,
                ::y,
                (x + y + this->field_202) % 15,
                1,
                0,
                0,
                0x1E0u,
                480,
                0);
            }
            else if ( *(_BYTE *)(dword_524EA8 + 3) != -1 )
            {
              IconToBitmap(
                (icon *)this->field_CE[39],
                gpWindowManager->screenBuffer,
                dword_524D10 - 32,
                ::y,
                *(_BYTE *)(dword_524EA8 + 3) - 62,
                1,
                0,
                0,
                0x1E0u,
                480,
                0);
            }
          }
        }
        if ( (((unsigned __int8)currentlyDrawnMapTile->bitfield_1_hasObject_1_isRoad_6_objTileset >> 2) & 0x3F) == 12 ) //monsters
        {
          if ( this->field_2B2 != x || this->field_2B6 != y )
          {
            IconToBitmap(
              (icon *)this->field_CE[20],
              gpWindowManager->screenBuffer,
              dword_524D10 + 16,
              ::y + 30,
              9 * currentlyDrawnMapTile->objectIndex,
              1,
              0,
              0,
              0x1E0u,
              480,
              0);
            if ( currentlyDrawnMapTile->objectIndex != 59 && currentlyDrawnMapTile->objectIndex != 60 )
              dword_524D14 = (unsigned __int8)monAnimDrawFrame[*(&this->field_20A + (x & 3))];
            else
              dword_524D14 = *(&this->field_20A + (x & 3)) % 6;
            IconToBitmap(
              (icon *)this->field_CE[20],
              gpWindowManager->screenBuffer,
              dword_524D10 + 16,
              ::y + 30,
              dword_524D14 + 9 * currentlyDrawnMapTile->objectIndex + 1,
              1,
              0,
              0,
              0x1E0u,
              480,
              0);
          }
          else
          {
            IconToBitmap(
              (icon *)this->field_CE[20],
              gpWindowManager->screenBuffer,
              dword_524D10 + 16,
              ::y + 30,
              8 - (this->field_2BA < 1u) + 9 * currentlyDrawnMapTile->objectIndex,
              1,
              0,
              0,
              0x1E0u,
              480,
              0);
          }
        }
      }
      if ( currentlyDrawnMapTile->objType == 171 ) //object type is boat
      {
        dword_524E74 = -1;
        dword_524EA0 = 6;
        spriteIdx = advManager::GetCursorBaseFrame(gpGame->boats[(unsigned __int8)((unsigned __int8)(currentlyDrawnMapTile->field_4_1_1_isShadow_1_13_extraInfo >> 8) >> -5)].field_3);
        dword_524D04 = 1;
        dword_524D2C = -10;
      }
      else
      {
        dword_524D2C = 0;
        if ( currentlyDrawnMapTile->objType == 170 ) //object type is hero
        {
          dword_524CDC = (int)&gpGame->heroes[(unsigned __int8)((unsigned __int8)(currentlyDrawnMapTile->field_4_1_1_isShadow_1_13_extraInfo >> 8) >> -5)];
          dword_524E74 = gpGame->players[*(_BYTE *)(dword_524CDC + 3)].color;
          dword_524EA0 = *(_BYTE *)(dword_524CDC + 227) & 0x80 ? 6 : *(_BYTE *)(dword_524CDC + 23);
          spriteIdx = advManager::GetCursorBaseFrame(*(_BYTE *)(dword_524CDC + 44));
          dword_524D04 = 1;
          if ( *(_BYTE *)(dword_524CDC + 227) & 0x80 )
            dword_524D2C = -10;
        }
      }
      if ( dword_524D04 )  //is hero or boat
      {
        if ( spriteIdx & 0x80 )
        {
          if ( DRAW_MASK & 0x80 )
          {
            if ( this->field_276 && dword_524EA0 != 6 )
            {
              v11 = spriteIdx & 0x7F;
              if ( v11 == 51 )
                v11 = 56;
              if ( v11 == 50 )
                v11 = 57;
              if ( v11 == 49 )
                v11 = 58;
              if ( v11 == 47 )
                v11 = 55;
              if ( v11 == 46 )
                v11 = 55;
              if ( v11 < 9 || v11 >= 36 )
                v9 = 0;
              else
                v9 = 50;
              IconToBitmap(
                this->shadowIcon,
                gpWindowManager->screenBuffer,
                dword_524D10,
                ::y + 31,
                v9 + v11,
                1,
                0,
                0,
                0x1E0u,
                480,
                0);
            }
            if ( this->field_276 && dword_524EA0 == 6 )
            {
              v10 = spriteIdx & 0x7F;
              if ( v10 < 9 || v10 >= 36 )
                v8 = 0;
              else
                v8 = 36;
              IconToBitmap(
                this->boatShadowIcon,
                gpWindowManager->screenBuffer,
                dword_524D10,
                dword_524D2C + ::y + 31,
                v8 + v10,
                1,
                0,
                0,
                0x1E0u,
                480,
                0);
            }
          }
          else
          {
            if ( dword_524EA0 == 6 && !(currentlyDrawnMapTile->displayFlags & 4) )
              FlipIconToBitmap(
                this->frothIcon,
                gpWindowManager->screenBuffer,
                dword_524D10 + 32,
                dword_524D2C + ::y + 31,
                spriteIdx & 0x7F,
                1,
                0,
                0,
                480,
                480,
                0);
            FlipIconToBitmap(
              (icon *)this->heroIcons[dword_524EA0],
              gpWindowManager->screenBuffer,
              dword_524D10 + 32,
              dword_524D2C + ::y + 31,
              spriteIdx & 0x7F,
              1,
              0,
              0,
              480,
              480,
              0);
            if ( dword_524E74 != -1 )
            {
              if ( dword_524EA0 == 6 )
                FlipIconToBitmap(
                  (icon *)this->flagIcons2[dword_524E74],
                  gpWindowManager->screenBuffer,
                  dword_524D10 + 32,
                  dword_524D2C + ::y + 31,
                  spriteIdx & 0x7F,
                  1,
                  0,
                  0,
                  480,
                  480,
                  0);
              else
                FlipIconToBitmap(
                  (icon *)this->flagIcons1[dword_524E74],
                  gpWindowManager->screenBuffer,
                  dword_524D10 + 32,
                  ::y + 31,
                  (spriteIdx & 0x7F)
                + (((unsigned __int64)this->field_202 >> 32) ^ abs(this->field_202) & 7)
                - ((unsigned __int64)this->field_202 >> 32)
                + 56,
                  1,
                  0,
                  0,
                  480,
                  480,
                  0);
            }
          }
        }
        else if ( DRAW_MASK & 0x80 )
        {
          if ( this->field_276 && dword_524EA0 != 6 && DRAW_MASK & 0x80 )
            IconToBitmap(
              this->shadowIcon,
              gpWindowManager->screenBuffer,
              dword_524D10,
              ::y + 31,
              spriteIdx,
              1,
              0,
              0,
              0x1E0u,
              480,
              0);
          if ( this->field_276 && dword_524EA0 == 6 )
            IconToBitmap(
              this->boatShadowIcon,
              gpWindowManager->screenBuffer,
              dword_524D10,
              dword_524D2C + ::y + 31,
              spriteIdx,
              1,
              0,
              0,
              0x1E0u,
              480,
              0);
        }
        else
        {
          if ( dword_524EA0 == 6 && !(currentlyDrawnMapTile->displayFlags & 4) )
            IconToBitmap(
              this->frothIcon,
              gpWindowManager->screenBuffer,
              dword_524D10,
              dword_524D2C + ::y + 31,
              spriteIdx,
              1,
              0,
              0,
              0x1E0u,
              480,
              0);
          IconToBitmap(
            (icon *)this->heroIcons[dword_524EA0],
            gpWindowManager->screenBuffer,
            dword_524D10,
            dword_524D2C + ::y + 31,
            spriteIdx,
            1,
            0,
            0,
            0x1E0u,
            480,
            0);
          if ( dword_524E74 != -1 )
          {
            if ( dword_524EA0 == 6 )
              IconToBitmap(
                (icon *)this->flagIcons2[dword_524E74],
                gpWindowManager->screenBuffer,
                dword_524D10,
                dword_524D2C + ::y + 31,
                spriteIdx & 0x7F,
                1,
                0,
                0,
                0x1E0u,
                480,
                0);
            else
              IconToBitmap(
                (icon *)this->flagIcons1[dword_524E74],
                gpWindowManager->screenBuffer,
                dword_524D10,
                ::y + 31,
                (spriteIdx & 0x7F)
              + (((unsigned __int64)this->field_202 >> 32) ^ abs(this->field_202) & 7)
              - ((unsigned __int64)this->field_202 >> 32)
              + 56,
                1,
                0,
                0,
                0x1E0u,
                480,
                0);
          }
        }
      }
      if ( this->field_272
        && currentlyDrawnMapTile->displayFlags & 0x40
        && (!this->field_2A2 || DRAW_MASK & 0x80)
        && this->viewX + 7 == x
        && this->viewY + 7 == y
        && !(DRAW_MASK & 0x80) )
      {
        advManager::DrawCursorShadow(this);
        advManager::DrawCursor(this);
        this->field_2A2 = 1;
      }
    }
    if ( DRAW_MASK & 4 || DRAW_MASK & 0x40 )
    {
      if ( DRAW_MASK & 4 && currentlyDrawnMapTile->objectIndex != 255 )
      {
        if ( (currentlyDrawnMapTile->field_4_1_1_isShadow_1_13_extraInfo >> 2) & 1
          && (!gbDrawingPuzzle
           || bPuzzleDraw[((unsigned __int8)currentlyDrawnMapTile->bitfield_1_hasObject_1_isRoad_6_objTileset >> 2) & 0x3F]) )
        {
          IconToBitmap(
            (icon *)this->field_CE[((unsigned __int8)currentlyDrawnMapTile->bitfield_1_hasObject_1_isRoad_6_objTileset >> 2) & 0x3F],
            gpWindowManager->screenBuffer,
            dword_524D10,
            ::y,
            currentlyDrawnMapTile->objectIndex,
            0,
            0,
            0,
            0x1E0u,
            480,
            0);
          if ( currentlyDrawnMapTile->bitfield_1_hasObject_1_isRoad_6_objTileset & 1 )
          {
            number_of_animation_frames = GetIconEntry(
                             (icon *)this->field_CE[((unsigned __int8)currentlyDrawnMapTile->bitfield_1_hasObject_1_isRoad_6_objTileset >> 2) & 0x3F],
                             currentlyDrawnMapTile->objectIndex)->someSortOfLength & 0x1F;
            IconToBitmap(
              (icon *)this->field_CE[((unsigned __int8)currentlyDrawnMapTile->bitfield_1_hasObject_1_isRoad_6_objTileset >> 2) & 0x3F],
              gpWindowManager->screenBuffer,
              dword_524D10,
              ::y,
              currentlyDrawnMapTile->objectIndex + this->field_202 % number_of_animation_frames + 1,
              0,
              0,
              0,
              0x1E0u,
              480,
              0);
          }
        }
        if ( currentlyDrawnMapTile->extraIdx
          && *(&this->map->cellExtras->objectIndex
             + 8 * currentlyDrawnMapTile->extraIdx
             - currentlyDrawnMapTile->extraIdx) != 255 )
          currentlyDrawingMapCellExtra = (mapCellExtra *)((char *)this->map->cellExtras
                                                        + 8 * currentlyDrawnMapTile->extraIdx
                                                        - currentlyDrawnMapTile->extraIdx);
        else
          currentlyDrawingMapCellExtra = 0;
        while ( currentlyDrawingMapCellExtra )
        {
          if ( ((unsigned __int8)currentlyDrawingMapCellExtra->field_4 >> 2) & 1
            && (!gbDrawingPuzzle || bPuzzleDraw[(currentlyDrawingMapCellExtra->_1_q_7_objTileset >> 1) & 0x7F]) )
          {
            IconToBitmap(
              (icon *)this->field_CE[(currentlyDrawingMapCellExtra->_1_q_7_objTileset >> 1) & 0x7F],
              gpWindowManager->screenBuffer,
              dword_524D10,
              ::y,
              currentlyDrawingMapCellExtra->objectIndex,
              0,
              0,
              0,
              0x1E0u,
              480,
              0);
            if ( currentlyDrawingMapCellExtra->_1_q_7_objTileset & 1 )
            {
              number_of_animation_frames = GetIconEntry(
                               (icon *)this->field_CE[(currentlyDrawingMapCellExtra->_1_q_7_objTileset >> 1) & 0x7F],
                               currentlyDrawingMapCellExtra->objectIndex)->someSortOfLength & 0x1F;
              IconToBitmap(
                (icon *)this->field_CE[(currentlyDrawingMapCellExtra->_1_q_7_objTileset >> 1) & 0x7F],
                gpWindowManager->screenBuffer,
                dword_524D10,
                ::y,
                currentlyDrawingMapCellExtra->objectIndex + this->field_202 % number_of_animation_frames + 1,
                0,
                0,
                0,
                0x1E0u,
                480,
                0);
            }
          }
          if ( currentlyDrawingMapCellExtra->nextIdx
            && *(&this->map->cellExtras->objectIndex
               + 8 * currentlyDrawingMapCellExtra->nextIdx
               - currentlyDrawingMapCellExtra->nextIdx) != 255 )
            currentlyDrawingMapCellExtra = (mapCellExtra *)((char *)this->map->cellExtras
                                                          + 8 * currentlyDrawingMapCellExtra->nextIdx
                                                          - currentlyDrawingMapCellExtra->nextIdx);
          else
            currentlyDrawingMapCellExtra = 0;
        }
      }
      if ( currentlyDrawnMapTile->overlayIndex != 255
        && (DRAW_MASK & 4
         && !(((unsigned __int8)currentlyDrawnMapTile->field__1_hasOverlay_1_hasLateOverlay_6_overlayTileset >> 1) & 1)
         || DRAW_MASK & 0x40
         && ((unsigned __int8)currentlyDrawnMapTile->field__1_hasOverlay_1_hasLateOverlay_6_overlayTileset >> 1) & 1) )
      {
        if ( !gbDrawingPuzzle
          || bPuzzleDraw[((unsigned __int8)currentlyDrawnMapTile->field__1_hasOverlay_1_hasLateOverlay_6_overlayTileset >> 2) & 0x3F] )
        {
          IconToBitmap(
            (icon *)this->field_CE[((unsigned __int8)currentlyDrawnMapTile->field__1_hasOverlay_1_hasLateOverlay_6_overlayTileset >> 2) & 0x3F],
            gpWindowManager->screenBuffer,
            dword_524D10,
            ::y,
            currentlyDrawnMapTile->overlayIndex,
            (((unsigned __int8)currentlyDrawnMapTile->field__1_hasOverlay_1_hasLateOverlay_6_overlayTileset >> 2) & 0x3F) == 14,
            0,
            0,
            0x1E0u,
            480,
            0);
          if ( currentlyDrawnMapTile->field__1_hasOverlay_1_hasLateOverlay_6_overlayTileset & 1 )
          {
            number_of_animation_frames = GetIconEntry(
                             (icon *)this->field_CE[((unsigned __int8)currentlyDrawnMapTile->field__1_hasOverlay_1_hasLateOverlay_6_overlayTileset >> 2) & 0x3F],
                             currentlyDrawnMapTile->overlayIndex)->someSortOfLength & 0x1F;
            IconToBitmap(
              (icon *)this->field_CE[((unsigned __int8)currentlyDrawnMapTile->field__1_hasOverlay_1_hasLateOverlay_6_overlayTileset >> 2) & 0x3F],
              gpWindowManager->screenBuffer,
              dword_524D10,
              ::y,
              currentlyDrawnMapTile->overlayIndex + this->field_202 % number_of_animation_frames + 1,
              0,
              0,
              0,
              0x1E0u,
              480,
              0);
          }
        }
      }
      if ( currentlyDrawnMapTile->extraIdx
        && *(&this->map->cellExtras->field_6 + 8 * currentlyDrawnMapTile->extraIdx - currentlyDrawnMapTile->extraIdx) != 255 )
        currentlyDrawingMapCellExtra = (mapCellExtra *)((char *)this->map->cellExtras
                                                      + 8 * currentlyDrawnMapTile->extraIdx
                                                      - currentlyDrawnMapTile->extraIdx);
      else
        currentlyDrawingMapCellExtra = 0;
      while ( currentlyDrawingMapCellExtra )
      {
        if ( DRAW_MASK & 4 && !(((unsigned __int8)currentlyDrawingMapCellExtra->_1_q_1_hasLateOverlay_6_q >> 1) & 1)
          || DRAW_MASK & 0x40 && ((unsigned __int8)currentlyDrawingMapCellExtra->_1_q_1_hasLateOverlay_6_q >> 1) & 1 )
        {
          if ( !gbDrawingPuzzle
            || bPuzzleDraw[((unsigned __int8)currentlyDrawingMapCellExtra->_1_q_1_hasLateOverlay_6_q >> 2) & 0x3F] )
          {
            IconToBitmap(
              (icon *)this->field_CE[((unsigned __int8)currentlyDrawingMapCellExtra->_1_q_1_hasLateOverlay_6_q >> 2) & 0x3F],
              gpWindowManager->screenBuffer,
              dword_524D10,
              ::y,
              currentlyDrawingMapCellExtra->field_6,
              (((unsigned __int8)currentlyDrawingMapCellExtra->_1_q_1_hasLateOverlay_6_q >> 2) & 0x3F) == 14,
              0,
              0,
              0x1E0u,
              480,
              0);
            if ( currentlyDrawingMapCellExtra->_1_q_1_hasLateOverlay_6_q & 1 )
            {
              number_of_animation_frames = GetIconEntry(
                               (icon *)this->field_CE[((unsigned __int8)currentlyDrawingMapCellExtra->_1_q_1_hasLateOverlay_6_q >> 2) & 0x3F],
                               currentlyDrawingMapCellExtra->field_6)->someSortOfLength & 0x1F;
              IconToBitmap(
                (icon *)this->field_CE[((unsigned __int8)currentlyDrawingMapCellExtra->_1_q_1_hasLateOverlay_6_q >> 2) & 0x3F],
                gpWindowManager->screenBuffer,
                dword_524D10,
                ::y,
                currentlyDrawingMapCellExtra->field_6 + this->field_202 % number_of_animation_frames + 1,
                0,
                0,
                0,
                0x1E0u,
                480,
                0);
            }
          }
        }
        if ( currentlyDrawingMapCellExtra->nextIdx
          && *(&this->map->cellExtras->field_6
             + 8 * currentlyDrawingMapCellExtra->nextIdx
             - currentlyDrawingMapCellExtra->nextIdx) != 255 )
          currentlyDrawingMapCellExtra = (mapCellExtra *)((char *)this->map->cellExtras
                                                        + 8 * currentlyDrawingMapCellExtra->nextIdx
                                                        - currentlyDrawingMapCellExtra->nextIdx);
        else
          currentlyDrawingMapCellExtra = 0;
      }
    }
  }
  else if ( dword_524CF8 )
  {
    if ( dword_524CD4 )
      FlipIconToBitmap(
        this->clopIcon,
        gpWindowManager->screenBuffer,
        dword_524D10 + 31,
        ::y,
        dword_524D24 - 1,
        0,
        0,
        0,
        0,
        0,
        0);
    else
      IconToBitmap(this->clopIcon, gpWindowManager->screenBuffer, dword_524D10, ::y, dword_524D24 - 1, 0, 0, 0, 0, 0, 0);
  }
  else if ( this->field_A2 && *(_WORD *)(2 * x + 2 * MAP_WIDTH * y + this->sizeOfSomethingMapRelated) )
  { //draw route icon on top of map
    if ( (*(_WORD *)(2 * x + 2 * MAP_WIDTH * y + this->sizeOfSomethingMapRelated) >> 8) & 1 )
      IconToBitmapColorTable(
        (icon *)this->field_CE[17], //"route.icn"
        gpWindowManager->screenBuffer,
        dword_524D10 - 12,
        ::y + 2,
        (unsigned __int8)(*(_WORD *)(2 * x + 2 * MAP_WIDTH * y + this->sizeOfSomethingMapRelated) - 1),
        1,
        0,
        0,
        0x1E0u,
        480,
        0,
        gColorTableRed,
        1);
    else
      IconToBitmap(
        (icon *)this->field_CE[17], //"route.icn"
        gpWindowManager->screenBuffer,
        dword_524D10 - 12,
        ::y + 2,
        (unsigned __int8)(*(_WORD *)(2 * x + 2 * MAP_WIDTH * y + this->sizeOfSomethingMapRelated) - 1),
        1,
        0,
        0,
        0x1E0u,
        480,
        0);
  }
}