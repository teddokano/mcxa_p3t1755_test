void test_number_conversion( void )
{	
	uint16_t	us;
	float		t;
	
	for ( uint16_t i = 40; i < 50; i++ )
	{
		us	= celsius2short( (float)i / 2.0 );
		t	= short2celsius( us );
		
		PRINTF( "%2u, 0x%04X, %8.4f\r\n", i, us, t );		
	}
}
