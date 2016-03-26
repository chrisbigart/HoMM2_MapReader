
//----- (00420AB0) --------------------------------------------------------
int __thiscall game::LoadMap(game *ecx0, char *nam)
{
  char buf; // [sp+10h] [bp-20h]@22
  int fd; // [sp+18h] [bp-18h]@1
  char y; // [sp+1Ch] [bp-14h]@5
  int i; // [sp+20h] [bp-10h]@3
  char x; // [sp+24h] [bp-Ch]@5
  char alignmentAndCastle; // [sp+28h] [bp-8h]@5

  sprintf(gText, "%s%s", ".\\MAPS\\", nam);
  fd = open(gText, O_BINARY);
  if ( fd == -1 )
    FileError(gText);
  _read(fd, &ecx0->mapHeader, 0x1A4u);
  fullMap::Read(&ecx0->map, fd, 1);
  game::SetMapSize(ecx0, ecx0->map.width, ecx0->map.height);
  for ( i = 0; i < MAX_CASTLES; ++i )
  {
    _read(fd, &x, 1u);
    _read(fd, &y, 1u);
    _read(fd, &alignmentAndCastle, 1u);
    if ( (unsigned __int8)x != 255 )
    {
      ecx0->castles[i].exists = 1;
      ecx0->castles[i].x = x;
      ecx0->castles[i].y = y;
      ecx0->castles[i].factionID = alignmentAndCastle & 0x7F;
      if ( alignmentAndCastle >= 0 )
        ecx0->castles[i].buildingsBuiltFlags |= BUILDING_SPECIAL_DEFENSE_BUILT;
      else
        ecx0->castles[i].buildingsBuiltFlags |= 0x40u;
    }
  }
  for ( i = 0; i < 144; ++i )
  {
    if ( ecx0->mapHeader.field_0 != 90 || i < 72 )
    {
      _read(fd, &x, 1u);
      _read(fd, &y, 1u);
      _read(fd, &alignmentAndCastle, 1u);
    }
    else
    {
      x = -1;
      y = -1;
      alignmentAndCastle = -1;
    }
    if ( (unsigned __int8)x != 255 )
    {
      ecx0->mines[i].guardianType = -1;
      ecx0->mines[i].x = x;
      ecx0->mines[i].y = y;
      ecx0->mines[i].type = alignmentAndCastle;
    }
  }
  ecx0->mapHeader.field_0 = 92;
  _read(fd, &ecx0->numObelisks, 1u);
  _read(fd, ecx0->rumorIndices, 2 * ecx0->mapHeader.numRumors);
  ecx0->numRumors = ecx0->mapHeader.numRumors;
  _read(fd, ecx0->eventIndices, 2 * ecx0->mapHeader.numEvents);
  ecx0->numEvents = ecx0->mapHeader.numEvents;
  _read(fd, &iMaxMapExtra, 4u);
  ppMapExtra = (void **)BaseAlloc(4 * iMaxMapExtra, "F:\\h2xsrc\\Source\\GAME.CPP", word_4EF3C0 + 89);
  pwSizeOfMapExtra = (__int16 *)BaseAlloc(2 * iMaxMapExtra, "F:\\h2xsrc\\Source\\GAME.CPP", word_4EF3C0 + 90);
  memset(ppMapExtra, 0, 4 * iMaxMapExtra);
  memset(pwSizeOfMapExtra, 0, 2 * iMaxMapExtra);
  for ( i = 1; i < iMaxMapExtra; ++i )
  {
    _read(fd, &pwSizeOfMapExtra[i], 2u);
    ppMapExtra[i] = BaseAlloc(pwSizeOfMapExtra[i], "F:\\h2xsrc\\Source\\GAME.CPP", word_4EF3C0 + 98);
    _read(fd, ppMapExtra[i], pwSizeOfMapExtra[i]);
  }
  _read(fd, &buf, 2u);
  _close(fd);
  return 0;
}
// 4EF3C0: using guessed type __int16 word_4EF3C0;




//----- (0046FE60) --------------------------------------------------------
BOOL __thiscall fullMap::Read(fullMap *this, UINT fd, int isNewGame)
{
  BOOL result; // eax@16
  void *v5; // [sp+28h] [bp-14h]@13
  void *buf; // [sp+2Ch] [bp-10h]@2
  int j; // [sp+30h] [bp-Ch]@4
  int i; // [sp+34h] [bp-8h]@2
  int k; // [sp+38h] [bp-4h]@13

  _read(fd, &this->width, 4u);
  _read(fd, &this->height, 4u);
  fullMap::Init(this, this->width, this->height);
  if ( isNewGame )
  {
    buf = operator new(20 * this->height * this->width);
    _read(fd, buf, 20 * this->height * this->width);
    for ( i = 0; this->width > i; ++i )
    {
      for ( j = 0; this->height > j; ++j )
        memcpy(&this->tiles[j * this->width] + i, (char *)buf + 20 * i + 20 * j * this->width, sizeof(mapCell));
    }
    operator delete(buf);
  }
  else
  {
    _read(fd, this->tiles, sizeof(mapCell) * this->height * this->width);
  }
  _read(fd, &this->numCellExtras, 4u);
  if ( this->cellExtras )
    operator delete(this->cellExtras);
  this->cellExtras = (mapCellExtra *)operator new(7 * this->numCellExtras);
  if ( isNewGame )
  {
    v5 = operator new(15 * this->numCellExtras);
    _read(fd, v5, 15 * this->numCellExtras);
    for ( k = 0; this->numCellExtras > k; ++k )
      memcpy((char *)this->cellExtras + 8 * k - k, (char *)v5 + 15 * k, 7u);
    result = operator delete(v5);
  }
  else
  {
    result = _read(fd, this->cellExtras, 7 * this->numCellExtras);
  }
  return result;
}