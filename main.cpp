/*
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
 */

#include "cube.h"

static void writelog(FILE *file, const char *buf)
{
    static uchar ubuf[512];
    size_t len = strlen(buf), carry = 0;
    while(carry < len)
    {
        size_t numu = encodeutf8(ubuf, sizeof(ubuf)-1, &((const uchar *)buf)[carry], len - carry, &carry);
        if(carry >= len) ubuf[numu++] = '\n';
        fwrite(ubuf, 1, numu, file);
    }
}

void logoutfv(const char *fmt, va_list args)
{
	static char buf[512];
    vformatstring(buf, fmt, args, sizeof(buf));
    writelog(stdout, buf);
}


void fatal(const char *fmt, ...)
{
    exit(EXIT_FAILURE);
}

void conoutfv(int type, const char *fmt, va_list args)
{
    logoutfv(fmt, args);
}

void conoutf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    conoutfv(CON_INFO, fmt, args);
    va_end(args);
}

void conoutf(int type, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    conoutfv(type, fmt, args);
    va_end(args);
}
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


int main(int argc, char* argv[])
{
	vector<char> line;
	for(int i=1;i<argc;i++)
	{
		if(argv[i][0] == '-')
		{
			switch(argv[i][1])
			{
				case 'f':  //file
					execfile(argv[i]+2);
					break;

				case 'e': //evaluate
					execute(argv[i]+2);
					break;
					
				case 'h' : //help
					printf("Valid options: -f (executes file), -e (evaluates input) \n");
					break;

				default:
					conoutf("unkown option!");
					break;
			}
		}
	}

	return 0;
}



