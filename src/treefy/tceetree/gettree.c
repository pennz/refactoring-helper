/*
 * This source code is released for free distribution under the terms of the MIT License (MIT):
 *
 * Copyright (c) 2014, Fabio Visona'
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef _ALL_IN_ONE
#include "defines.h"
#include "slib.h"
#include "gettree.h"
#endif // _ALL_IN_ONE

#define MAXLINEF			5000					// maximum length of a line in cscope.out

void replendline(char * sline)
{
	int i;

	for (i = 2; i < MAXLINEF && sline[i] != 0; i++)
	{
		if (sline[i] == '\n')
			sline[i] = 0;
	}
}

int gettree(ttree_t *ptree, treeparam_t *pparam)
{
	int iErr = 0;
	FILE *filein, *filedbout;
	char sLine[MAXLINEF];
	char *sSub;
	char *sfilename = NULL;
	char *scaller = NULL;
	ttreenode_t *ncaller, *ncallee;
	long lineidx;

	/* Get all Nodes */
	filein = fopen(pparam->infile, "r");
	if (filein == NULL)
	{
		printf("\nError while opening input file\n");
		iErr = -1;
	}
	else
	{
		if (iErr == 0)
		{
			filedbout = NULL;
			if (pparam->shortdbfile[0] != 0)
			{
				filedbout = fopen(pparam->shortdbfile, "w");
				if (filedbout == NULL)
				{
					printf("\nError while opening shortened cscope db file\n");
					iErr = -1;
				}
			}
		}
			
		if (iErr == 0)
		{
			filein = fopen(pparam->infile, "r");
			if (filein == NULL)
			{
				printf("\nError while opening input file\n");
				iErr = -1;
			}
			else
			{
				lineidx = 0;		
				if (pparam->verbose)
					printf("\n");
				while (iErr == 0 && fgets(sLine, MAXLINEF, filein) != NULL)
				{
					lineidx++;					
					if (pparam->verbose)
					{
						printf("Getting tree nodes... line %ld\r", lineidx);
					}
					switch (sLine[0])
					{
						case '\t':
							switch (sLine[1])
							{
								case '@':
									// filename where function is defined
									if (filedbout != NULL)
										fputs(sLine, filedbout);
									replendline(sLine);
									sSub = &sLine[2];
									iErr = slibcpy(&sfilename, sSub, -1);
									break;

								case '$':
									// add one node for each function definition
									if (filedbout != NULL)
										fputs(sLine, filedbout);
									replendline(sLine);
									sSub = &sLine[2];
									iErr = ttreeaddnode(ptree, sSub, sfilename);
									break;

								case '`':
									if (filedbout != NULL)
										fputs(sLine, filedbout);
									break;	

								default:
									break;
							}
							break;

						default:
							break;
					}
				}

				if (lineidx == 0)
				{
					printf("\nInput file is empty\n");
					iErr = -1;
				}
				
				if (fclose(filein) != 0)
				{
					printf("\nError while closing input file\n");
					iErr = -1;
				}

				if (filedbout != NULL && fclose(filedbout) != 0)
				{
					printf("\nError while closing shortened cscope db file\n");
					iErr = -1;
				}				
			}
		}
	}

	if (iErr == 0)
	{
		/* Get all Branches */
		filein = fopen(pparam->infile, "r");
		if (filein == NULL)
		{
			printf("\nError while opening input file\n");
			iErr = -1;
		}
		else
		{
			if (pparam->verbose)
				printf("\n");
			lineidx = 0;
			while (iErr == 0 && fgets(sLine, MAXLINEF, filein) != NULL)
			{
				if (pparam->verbose)
				{
					lineidx++;
					printf("Getting tree branches... line %ld\r", lineidx);
				}
				switch (sLine[0])
				{
					case '\t':
						switch (sLine[1])
						{
							case '@':
								// get again filename where caller is defined
								replendline(sLine);
								sSub = &sLine[2];
								iErr = slibcpy(&sfilename, sSub, -1);
								break;

							case '$':
								// get the name of caller function
								replendline(sLine);
								sSub = &sLine[2];
								iErr = slibcpy(&scaller, sSub, -1);
								break;

							case '`':
								replendline(sLine);
								sSub = &sLine[2];
								if (sfilename)
								{
									// find the caller function node
									ncaller = ttreefindnode(ptree, scaller, sfilename);
									if (ncaller != NULL)
									{
										// find the callee function node
										ncallee = ttreefindnode(ptree, sSub, NULL);
										if (ncallee == NULL)
										{
											// could not find the callee function: it must be a library function:
											// create its node now
											iErr = ttreeaddnode(ptree, sSub, NULL);
											if (iErr == 0)
												ncallee = ptree->lastnode;
										}
										// add branch
										if (iErr == 0)
											iErr = ttreeaddbranch(ptree, ncaller, ncallee, sfilename);
									}
									/* Comment here: better to go on; it may happen to come
									 * here in cases like: #define FUN() funct(a, b)
									else
									{
										// this should never happen
										printf("\nCaller function node not found\n");
										iErr = -1;
									}
									*/
								}
								else
								{
									printf("\nFilename where the call is has not been found\n");
									iErr = -1;
								}
								break;

							default:
								break;
						}
						break;

					default:
						break;
				}
			}

			if (fclose(filein) != 0)
			{
				printf("\nError while closing input file\n");
				iErr = -1;
			}
		}
	}

	free(sfilename);
	free(scaller);

	return iErr;
}

