void MousePositionInit( 
    MousePosition* this, Compass forwardDir, int startingX, int startingY)
{
    this->forwardDirection = forwardDir;
    this->x = startingX; 
    this->y = startingY;
}

void MousePositionGoForward(MousePosition* this)
{
    if (this->forwardDirection == NORTH) this->y -= 1;
    if (this->forwardDirection == SOUTH) this->y += 1;
    if (this->forwardDirection == WEST)  this->x -= 1;
    if (this->forwardDirection == EAST)  this->x += 1;

    if (this->y < 0) this->y = 0;
    if (this->y > 13) this->y = 13;
    if (this->x < 0) this->x = 0;
    if (this->x > 13) this->x = 13;
}

void MousePositionGoBackward(MousePosition* this)
{
    if (this->forwardDirection == SOUTH)
    {
    	this->forwardDirection = NORTH;
    	this->y -= 1;
    }

    else if (this->forwardDirection == NORTH)
    {
    	this->forwardDirection = SOUTH;
    	this->y += 1;
    }

    else if (this->forwardDirection == EAST)
    {
    	this->forwardDirection = WEST;
        this->x -= 1;
    }

    else if (this->forwardDirection == WEST)
    {
    	this->forwardDirection = EAST;
    	this->x += 1;
    }

    if (this->y < 0) this->y = 0;
    if (this->y > 13) this->y = 13;
    if (this->x < 0) this->x = 0;
    if (this->x > 13) this->x = 13;
}

void MousePositionRotateLeft(MousePosition* this)
{
    if (this->forwardDirection == NORTH)
        this->forwardDirection = WEST;
    else if (this->forwardDirection == SOUTH)
        this->forwardDirection = EAST;
    else if (this->forwardDirection == WEST)
        this->forwardDirection = SOUTH;
    else if (this->forwardDirection == EAST)
        this->forwardDirection = NORTH;
}

void MousePositionRotateRight(MousePosition* this)
{
    if (this->forwardDirection == NORTH)
        this->forwardDirection = EAST;
    else if (this->forwardDirection == SOUTH)
        this->forwardDirection = WEST;
    else if (this->forwardDirection == WEST)
        this->forwardDirection = NORTH;
    else if (this->forwardDirection == EAST)
        this->forwardDirection = SOUTH;
}

void MousePositionRotateBackwards(MousePosition* this)
{
    if (this->forwardDirection == NORTH)
        this->forwardDirection = SOUTH;
    else if (this->forwardDirection == SOUTH)
        this->forwardDirection = NORTH;
    else if (this->forwardDirection == WEST)
        this->forwardDirection = EAST;
    else if (this->forwardDirection == EAST)
        this->forwardDirection = WEST;
}
