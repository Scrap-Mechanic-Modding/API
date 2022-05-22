#pragma once



namespace SMM
{
    namespace Utility
    {
        class VtableDatabase
        {
        public:
            VtableDatabase(VtableDatabase const&) = delete;
            void operator=(VtableDatabase const&) = delete;

            static VtableDatabase& GetInstance()
            {
                static VtableDatabase s_instance;
                return s_instance;
            }

        private:
            VtableDatabase()
            {
            }
        };
    } // namespace Utility
} // namespace SMM
